#!/usr/bin/env python3
"""
Codeforces Solutions Repository Auto-Generator
Scans repo, matches problems via CF API, generates charts + README.
"""

import os
import re
import json
import subprocess
from datetime import datetime, timedelta
from collections import Counter, defaultdict
from difflib import SequenceMatcher
from pathlib import Path
from urllib.request import urlopen, Request
from urllib.error import URLError
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import numpy as np

# ─── Config ──────────────────────────────────────────────────────────────────
ROOT = Path(__file__).parent
ASSETS = ROOT / "assets"
DATA = ROOT / "data"
ASSETS.mkdir(exist_ok=True)
DATA.mkdir(exist_ok=True)

CF_HANDLE = os.environ.get("CF_HANDLE", "")
SKIP_DIRS = {".git", "node_modules", "__pycache__", ".github", "assets", "data", ".claude"}
SKIP_FILES = {"tempCodeRunnerFile.cpp", "hello.cpp", "Skeleton.cpp", "test.cpp", "vectorTest.cpp"}

CF_COLORS = {
    "800": "#00b8a3", "900": "#009688", "1000": "#ffc107",
    "1100": "#ff9800", "1200": "#ff5722", "1300": "#f44336",
    "1400": "#e91e63", "1500": "#9c27b0", "1600": "#673ab7",
    "1700": "#3f51b5", "1800": "#2196f3", "1900": "#03a9f4",
    "2000": "#00bcd4", "2100": "#009688", "2200": "#4caf50",
    "2300": "#8bc34a", "2400": "#cddc39", "2500": "#ffeb3b",
}
DEFAULT_COLOR = "#ffffff"

TAG_EMOJI = {
    "implementation": "⚙️", "math": "🔢", "greedy": "💰", "dp": "📈",
    "strings": "📝", "string": "📝", "data structures": "🏗️",
    "sorting": "📊", "brute force": "🔨", "constructive algorithms": "🧱",
    "binary search": "🔍", "dfs and similar": "🌲", "bfs": "🌊",
    "graphs": "🕸️", "trees": "🌳", "bitmasks": "🎭", "number theory": "📐",
    "geometry": "📐", "combinatorics": "🎲", "probabilities": "🎰",
    "games": "🎮", "two pointers": "👆", "meet-in-the-middle": "🤝",
    "divide and conquer": "✂️", "shortest paths": "🛤️", "hashing": "#️⃣",
}


# ─── Helpers ─────────────────────────────────────────────────────────────────
def cf_get(endpoint, params=None):
    """Fetch from Codeforces API with caching."""
    url = f"https://codeforces.com/api/{endpoint}"
    if params:
        url += "?" + "&".join(f"{k}={v}" for k, v in params.items())
    cache_key = re.sub(r"[^a-z0-9]", "_", endpoint + ("_" + str(params) if params else ""))
    cache_file = DATA / f"{cache_key}.json"

    if cache_file.exists():
        age = datetime.now().timestamp() - cache_file.stat().st_mtime
        if age < 86400:  # 24h
            try:
                return json.loads(cache_file.read_text())
            except json.JSONDecodeError:
                pass

    try:
        req = Request(url, headers={"User-Agent": "CF-Repo-Generator/1.0"})
        resp = urlopen(req, timeout=15)
        data = json.loads(resp.read().decode())
        if data.get("status") == "OK":
            cache_file.write_text(json.dumps(data, indent=2))
            return data
    except Exception as e:
        print(f"  [WARN] API request failed for {endpoint}: {e}")
    return None


def git_date(filepath):
    """Get last commit date of a file."""
    try:
        r = subprocess.run(
            ["git", "log", "-1", "--format=%ai", "--", str(filepath)],
            capture_output=True, text=True, cwd=str(ROOT), timeout=10
        )
        if r.stdout.strip():
            return datetime.strptime(r.stdout.strip()[:19], "%Y-%m-%d %H:%M:%S")
    except Exception:
        pass
    return None


def normalize_name(name):
    """Normalize a problem name for matching."""
    name = name.lower().strip()
    # CamelCase → spaces
    name = re.sub(r"([a-z])([A-Z])", r"\1 \2", name)
    # Replace non-alphanumeric with spaces
    name = re.sub(r"[^a-z0-9]+", " ", name)
    # Collapse spaces
    name = re.sub(r"\s+", " ", name).strip()
    return name


def extract_difficulty(path_parts):
    """Extract difficulty rating from path components."""
    for part in path_parts:
        m = re.match(r"(\d{3,4})\s*(Rated)?", part, re.IGNORECASE)
        if m:
            return int(m.group(1))
    return None


def extract_topic(path_parts):
    """Extract topic from path components."""
    skip = SKIP_DIRS | {"Contest Ques"}
    for part in path_parts:
        if part in skip:
            continue
        m = re.match(r"\d{3,4}\s*(Rated)?", part, re.IGNORECASE)
        if m:
            continue
        return part.strip()
    return "Uncategorized"


# ─── Repo Scanner ────────────────────────────────────────────────────────────
def scan_repo():
    """Walk repo and collect all solution files with metadata."""
    solutions = []
    for dirpath, dirnames, filenames in os.walk(ROOT):
        dirnames[:] = [d for d in dirnames if d not in SKIP_DIRS]
        rel = Path(dirpath).relative_to(ROOT)
        parts = list(rel.parts)

        for f in filenames:
            if f in SKIP_FILES or not f.endswith((".cpp", ".py", ".java")):
                continue

            ext = f.rsplit(".", 1)[-1]
            filepath = Path(dirpath) / f
            rel_path = filepath.relative_to(ROOT)

            # Parse folder structure
            is_contest = "Contest Ques" in parts
            difficulty = extract_difficulty(parts)
            topic = extract_topic(parts)

            # For contest folders, try to extract date
            contest_date = None
            contest_div = None
            for p in parts:
                dm = re.search(r"(\d{2})(\w+)$", p)  # e.g., 26July, 30June
                if dm:
                    try:
                        contest_date = datetime.strptime(f"{dm.group(1)} {dm.group(2)}", "%d %B")
                    except ValueError:
                        pass
                if re.search(r"DIV\.?\s*\d", p, re.IGNORECASE):
                    dm2 = re.search(r"DIV\.?\s*(\d)", p, re.IGNORECASE)
                    if dm2:
                        contest_div = int(dm2.group(1))

            # Normalize problem name from filename
            problem_name = f.rsplit(".", 1)[0]  # strip extension

            # Get git date
            gd = git_date(rel_path)

            solutions.append({
                "file": str(rel_path),
                "filename": f,
                "problem_name": problem_name,
                "normalized": normalize_name(problem_name),
                "language": ext,
                "difficulty": difficulty,
                "topic": topic,
                "is_contest": is_contest,
                "contest_date": contest_date,
                "contest_div": contest_div,
                "git_date": gd,
                "matched_problem": None,
            })

    # Filter out test/skeleton files even if extension matches
    solutions = [s for s in solutions if "test" not in s["filename"].lower().replace("unittest", "")]
    print(f"  Found {len(solutions)} solution files")
    return solutions


# ─── Problem Matching ────────────────────────────────────────────────────────
def match_problems(solutions):
    """Match local files to Codeforces problems using the problemset API."""
    # Load or fetch problemset
    mapping_file = DATA / "mapping.json"
    saved_mapping = {}
    if mapping_file.exists():
        try:
            saved_mapping = json.loads(mapping_file.read_text())
        except json.JSONDecodeError:
            pass

    # Always try to fetch fresh problemset for matching
    print("  Fetching Codeforces problemset...")
    data = cf_get("problemset.problems")
    if not data:
        print("  [WARN] Could not fetch problemset — using saved mapping only")
        for sol in solutions:
            key = sol["file"]
            if key in saved_mapping:
                sol["matched_problem"] = saved_mapping[key]
        return

    problems = data["result"]["problems"]

    # Build lookup structures
    problems_by_rating = defaultdict(list)
    problems_by_normalized = {}
    for p in problems:
        pname = p.get("name", "")
        norm = normalize_name(pname)
        problems_by_normalized[norm] = p
        rating = p.get("rating")
        if rating:
            problems_by_rating[int(rating)].append(p)

    matched_count = 0
    for sol in solutions:
        key = sol["file"]

        # Check saved mapping first
        if key in saved_mapping:
            sol["matched_problem"] = saved_mapping[key]
            matched_count += 1
            continue

        norm = sol["normalized"]
        diff = sol["difficulty"]

        # Try exact match
        if norm in problems_by_normalized:
            p = problems_by_normalized[norm]
            sol["matched_problem"] = p
            matched_count += 1
            continue

        # Try fuzzy match
        candidates = problems_by_rating.get(diff, problems) if diff else problems
        best_match = None
        best_score = 0

        for p in candidates:
            pname_norm = normalize_name(p.get("name", ""))
            score = SequenceMatcher(None, norm, pname_norm).ratio()

            # Bonus for substring match
            if norm in pname_norm or pname_norm in norm:
                score = max(score, 0.85)

            if score > best_score:
                best_score = score
                best_match = p

        if best_match and best_score >= 0.65:
            sol["matched_problem"] = best_match
            matched_count += 1
            # Save mapping
            saved_mapping[key] = best_match

    # Save mapping
    mapping_file.write_text(json.dumps(saved_mapping, indent=2))
    print(f"  Matched {matched_count}/{len(solutions)} solutions to CF problems")


# ─── Analytics ───────────────────────────────────────────────────────────────
def compute_analytics(solutions, user_info=None, submissions=None):
    """Compute all statistics from matched solutions."""
    stats = {}

    # Basic counts
    stats["total"] = len(solutions)
    stats["languages"] = Counter(s["language"] for s in solutions)

    # Difficulty distribution
    diff_dist = Counter()
    for s in solutions:
        d = s["difficulty"]
        if d:
            diff_dist[d] += 1
        elif s["matched_problem"] and s["matched_problem"].get("rating"):
            diff_dist[s["matched_problem"]["rating"]] += 1
        else:
            diff_dist["Unrated"] += 1
    stats["difficulty_dist"] = dict(sorted(diff_dist.items(), key=lambda x: int(x[0]) if str(x[0]).isdigit() else 0))

    # Topic distribution
    topic_dist = Counter()
    for s in solutions:
        topic_dist[s["topic"]] += 1
    # Also count CF tags
    tag_dist = Counter()
    for s in solutions:
        mp = s.get("matched_problem")
        if mp:
            for tag in mp.get("tags", []):
                tag_dist[tag] += 1
    stats["topic_dist"] = dict(topic_dist.most_common(15))
    stats["tag_dist"] = dict(tag_dist.most_common(15))

    # Matched problems
    matched = [s for s in solutions if s["matched_problem"]]
    stats["matched_count"] = len(matched)

    # Hardest problems
    by_rating = []
    for s in matched:
        mp = s["matched_problem"]
        rating = mp.get("rating", 0)
        if rating:
            by_rating.append({"name": mp.get("name", ""), "rating": rating,
                              "contestId": mp.get("contestId", ""), "index": mp.get("index", ""),
                              "url": f"https://codeforces.com/problemset/problem/{mp.get('contestId')}/{mp.get('index')}",
                              "tags": mp.get("tags", [])})
    stats["hardest"] = sorted(by_rating, key=lambda x: -x["rating"])[:10]

    # Rating buckets
    buckets = {"Easy (800)": 0, "Easy (900)": 0, "Medium (1000-1200)": 0,
               "Medium (1300-1500)": 0, "Hard (1600-1900)": 0, "Hard (2000+)": 0}
    for s in matched:
        r = s["matched_problem"].get("rating", 0)
        if r <= 800: buckets["Easy (800)"] += 1
        elif r <= 900: buckets["Easy (900)"] += 1
        elif r <= 1200: buckets["Medium (1000-1200)"] += 1
        elif r <= 1500: buckets["Medium (1300-1500)"] += 1
        elif r <= 1900: buckets["Hard (1600-1900)"] += 1
        else: buckets["Hard (2000+)"] += 1
    stats["buckets"] = buckets

    # Monthly solves
    monthly = Counter()
    for s in solutions:
        d = s.get("git_date")
        if d:
            monthly[d.strftime("%Y-%m")] += 1
    stats["monthly_solves"] = dict(sorted(monthly.items()))

    # Solve dates for heatmap
    solve_dates = []
    for s in solutions:
        d = s.get("git_date")
        if d:
            solve_dates.append(d.date())
    stats["solve_dates"] = solve_dates

    # Streaks
    if solve_dates:
        unique_dates = sorted(set(solve_dates))
        longest = current = 1
        for i in range(1, len(unique_dates)):
            if (unique_dates[i] - unique_dates[i-1]).days == 1:
                current += 1
                longest = max(longest, current)
            elif (unique_dates[i] - unique_dates[i-1]).days > 1:
                current = 1
        # Current streak (from today backwards)
        today = datetime.now().date()
        current_streak = 0
        check = today
        date_set = set(unique_dates)
        while check in date_set:
            current_streak += 1
            check -= timedelta(days=1)
        stats["longest_streak"] = longest
        stats["current_streak"] = current_streak
        stats["first_solve"] = unique_dates[0]
        stats["last_solve"] = unique_dates[-1]
    else:
        stats["longest_streak"] = stats["current_streak"] = 0
        stats["first_solve"] = stats["last_solve"] = None

    # Contest solves
    contest_solves = [s for s in solutions if s["is_contest"]]
    stats["contest_solves"] = len(contest_solves)

    # User info
    stats["user_info"] = None
    if user_info and user_info.get("result"):
        ui = user_info["result"][0]
        stats["user_info"] = {
            "handle": ui.get("handle", ""),
            "rating": ui.get("rating", 0),
            "max_rating": ui.get("maxRating", 0),
            "rank": ui.get("rank", ""),
            "max_rank": ui.get("maxRank", ""),
        }

    # User submissions stats
    if submissions and submissions.get("result"):
        subs = submissions["result"]
        ac_subs = [s for s in subs if s.get("verdict") == "OK"]
        stats["cf_solved"] = len(set(
            (s["problem"].get("contestId", ""), s["problem"].get("index", ""))
            for s in ac_subs
        ))
        stats["cf_total_subs"] = len(subs)
        # Rating changes
        rating_data = []
        for s in subs:
            if "ratingChange" in s:
                rating_data.append({
                    "date": datetime.fromtimestamp(s.get("creationTimeSeconds", 0)),
                    "new_rating": s.get("newRating", 0),
                    "delta": s.get("ratingChange", 0),
                    "contest_id": s.get("contestId"),
                })
        stats["rating_history"] = sorted(rating_data, key=lambda x: x["date"])
    else:
        stats["cf_solved"] = 0
        stats["rating_history"] = []

    # Achievements
    achievements = []
    t = stats["total"]
    if t >= 10: achievements.append(("🏅", "10+ Problems", "Solved 10+ problems"))
    if t >= 25: achievements.append(("🥇", "25+ Problems", "Solved 25+ problems"))
    if t >= 50: achievements.append(("🏆", "50+ Problems", "Solved 50+ problems"))
    if t >= 100: achievements.append(("💎", "100+ Problems", "Century of problems!"))
    if t >= 150: achievements.append(("🔥", "150+ Problems", "Unstoppable grinder!"))
    if t >= 200: achievements.append(("⭐", "200+ Problems", "Absolute legend!"))
    if stats["longest_streak"] >= 7: achievements.append(("📅", "7-Day Streak", "Week-long grind!"))
    if stats["longest_streak"] >= 30: achievements.append(("🗓️", "30-Day Streak", "Monthly dedication!"))
    if len(stats["tag_dist"]) >= 5: achievements.append(("🎯", "Versatile", "5+ different tags"))
    if len(stats["tag_dist"]) >= 10: achievements.append(("🌈", "Polyglot Problem Solver", "10+ different tags"))
    if stats["hardest"] and stats["hardest"][0]["rating"] >= 1500:
        achievements.append(("💪", "Strong Solver", "Solved 1500+ rated problems"))
    if stats["hardest"] and stats["hardest"][0]["rating"] >= 2000:
        achievements.append(("🧠", "Expert Level", "Solved 2000+ rated problems"))
    if stats["contest_solves"] > 0:
        achievements.append(("🏁", "Contest Participant", f"{stats['contest_solves']} contest solves"))
    if stats["user_info"]:
        ui = stats["user_info"]
        if ui["rating"] >= 1200:
            achievements.append(("🔵", "Specialist", "CF rating 1200+"))
        if ui["rating"] >= 1400:
            achievements.append(("🟣", "Expert", "CF rating 1400+"))
        if ui["rating"] >= 1600:
            achievements.append(("🟠", "Candidate Master", "CF rating 1600+"))
        if ui["rating"] >= 1900:
            achievements.append(("🔴", "Master", "CF rating 1900+"))
    stats["achievements"] = achievements

    return stats


# ─── Chart Generation ────────────────────────────────────────────────────────
def setup_style():
    """Set up a dark modern chart style."""
    plt.rcParams.update({
        "figure.facecolor": "#0d1117",
        "axes.facecolor": "#161b22",
        "axes.edgecolor": "#30363d",
        "axes.labelcolor": "#c9d1d9",
        "text.color": "#c9d1d9",
        "xtick.color": "#8b949e",
        "ytick.color": "#8b949e",
        "grid.color": "#21262d",
        "grid.alpha": 0.8,
        "font.family": "sans-serif",
        "font.size": 11,
        "figure.dpi": 150,
        "savefig.dpi": 150,
        "savefig.bbox": "tight",
        "savefig.pad_inches": 0.3,
    })


def chart_difficulty(stats):
    """Bar chart of difficulty distribution."""
    dist = stats["difficulty_dist"]
    if not dist:
        return

    labels = []
    values = []
    colors = []
    for k, v in sorted(dist.items(), key=lambda x: int(x[0]) if str(x[0]).isdigit() else 9999):
        labels.append(str(k))
        values.append(v)
        colors.append(CF_COLORS.get(str(k), DEFAULT_COLOR))

    fig, ax = plt.subplots(figsize=(10, 5))
    bars = ax.bar(labels, values, color=colors, edgecolor="#30363d", linewidth=0.5)

    for bar, val in zip(bars, values):
        ax.text(bar.get_x() + bar.get_width()/2, bar.get_height() + 0.3,
                str(val), ha="center", va="bottom", fontweight="bold", color="#c9d1d9", fontsize=10)

    ax.set_xlabel("Problem Rating", fontsize=12, fontweight="bold")
    ax.set_ylabel("Count", fontsize=12, fontweight="bold")
    ax.set_title("Difficulty Distribution", fontsize=14, fontweight="bold", pad=15)
    ax.grid(axis="y", alpha=0.3)
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)

    plt.tight_layout()
    fig.savefig(ASSETS / "difficulty_dist.png")
    plt.close(fig)
    print("  ✅ difficulty_dist.png")


def chart_topics(stats):
    """Horizontal bar chart of tag distribution."""
    tags = stats.get("tag_dist", {})
    if not tags:
        tags = stats.get("topic_dist", {})
    if not tags:
        return

    sorted_tags = sorted(tags.items(), key=lambda x: x[1])[-15:]
    labels = [t.title() for t, _ in sorted_tags]
    values = [v for _, v in sorted_tags]

    fig, ax = plt.subplots(figsize=(10, max(4, len(labels) * 0.45)))
    gradient_colors = plt.cm.plasma(np.linspace(0.2, 0.85, len(labels)))
    ax.barh(labels, values, color=gradient_colors, edgecolor="#30363d", linewidth=0.5)

    for i, v in enumerate(values):
        ax.text(v + 0.2, i, str(v), va="center", fontweight="bold", color="#c9d1d9", fontsize=10)

    ax.set_xlabel("Count", fontsize=12, fontweight="bold")
    ax.set_title("Topic Distribution", fontsize=14, fontweight="bold", pad=15)
    ax.grid(axis="x", alpha=0.3)
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)

    plt.tight_layout()
    fig.savefig(ASSETS / "topic_dist.png")
    plt.close(fig)
    print("  ✅ topic_dist.png")


def chart_rating_progression(stats):
    """Line chart of CF rating over time."""
    history = stats.get("rating_history", [])
    if not history:
        return

    dates = [h["date"] for h in history]
    ratings = [h["new_rating"] for h in history]

    fig, ax = plt.subplots(figsize=(12, 5))
    ax.plot(dates, ratings, color="#58a6ff", linewidth=2.5, marker="o", markersize=4,
            markerfacecolor="#1f6feb", markeredgecolor="#58a6ff", markeredgewidth=1)

    # Fill under curve
    ax.fill_between(dates, ratings, alpha=0.15, color="#58a6ff")

    # Rating color bands
    for threshold, color, label in [
        (1200, "#00b8a3", "Specialist"), (1400, "#9c27b0", "Expert"),
        (1600, "#ff9800", "CM"), (1900, "#f44336", "Master"),
    ]:
        if min(ratings) < threshold <= max(ratings):
            ax.axhline(y=threshold, color=color, linestyle="--", alpha=0.4, linewidth=1)
            ax.text(dates[-1], threshold + 10, label, color=color, fontsize=8, alpha=0.7)

    ax.set_xlabel("Date", fontsize=12, fontweight="bold")
    ax.set_ylabel("Rating", fontsize=12, fontweight="bold")
    ax.set_title("Rating Progression", fontsize=14, fontweight="bold", pad=15)
    ax.grid(True, alpha=0.3)
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)
    ax.xaxis.set_major_formatter(mdates.DateFormatter("%b %Y"))
    fig.autofmt_xdate()

    plt.tight_layout()
    fig.savefig(ASSETS / "rating_chart.png")
    plt.close(fig)
    print("  ✅ rating_chart.png")


def chart_heatmap(stats):
    """GitHub-style contribution heatmap."""
    dates = stats.get("solve_dates", [])
    if not dates:
        return

    date_counts = Counter(dates)
    today = datetime.now().date()
    start = today - timedelta(days=364)

    # Build matrix (7 rows × 52 cols)
    weeks = 53
    matrix = np.zeros((7, weeks))
    all_dates = [start + timedelta(days=i) for i in range(365)]

    for d in all_dates:
        if d.weekday() < 7:
            week = (d - start).days // 7
            matrix[d.weekday()][week] = date_counts.get(d, 0)

    fig, ax = plt.subplots(figsize=(14, 3))
    # Custom colormap: dark → green
    from matplotlib.colors import LinearSegmentedColormap
    cmap = LinearSegmentedColormap.from_list("cf_heat",
        ["#161b22", "#0e4429", "#006d32", "#26a641", "#39d353"])
    ax.imshow(matrix, cmap=cmap, aspect="auto", interpolation="nearest")

    ax.set_yticks([0, 1, 2, 3, 4, 5, 6])
    ax.set_yticklabels(["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"], fontsize=9)
    ax.set_xticks([])
    ax.set_title("Activity Heatmap (Last 52 Weeks)", fontsize=14, fontweight="bold", pad=10)

    # Remove borders
    for spine in ax.spines.values():
        spine.set_visible(False)

    plt.tight_layout()
    fig.savefig(ASSETS / "activity_heatmap.png")
    plt.close(fig)
    print("  ✅ activity_heatmap.png")


def chart_monthly(stats):
    """Bar chart of monthly solves."""
    monthly = stats.get("monthly_solves", {})
    if not monthly:
        return

    labels = list(monthly.keys())[-12:]
    values = [monthly[l] for l in labels]

    fig, ax = plt.subplots(figsize=(10, 5))
    gradient = plt.cm.cool(np.linspace(0.3, 0.9, len(labels)))
    ax.bar(range(len(labels)), values, color=gradient, edgecolor="#30363d", linewidth=0.5)

    for i, v in enumerate(values):
        ax.text(i, v + 0.2, str(v), ha="center", fontweight="bold", color="#c9d1d9", fontsize=10)

    ax.set_xticks(range(len(labels)))
    ax.set_xticklabels(labels, rotation=45, ha="right", fontsize=9)
    ax.set_ylabel("Problems Solved", fontsize=12, fontweight="bold")
    ax.set_title("Monthly Solves", fontsize=14, fontweight="bold", pad=15)
    ax.grid(axis="y", alpha=0.3)
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)

    plt.tight_layout()
    fig.savefig(ASSETS / "monthly_solves.png")
    plt.close(fig)
    print("  ✅ monthly_solves.png")


def chart_language(stats):
    """Pie chart of language usage."""
    langs = stats.get("languages", {})
    if not langs:
        return

    lang_names = {"cpp": "C++", "py": "Python", "java": "Java"}
    labels = [lang_names.get(l, l.upper()) for l in langs.keys()]
    values = list(langs.values())
    colors = ["#3f51b5", "#ffc107", "#ff5722", "#4caf50"][:len(labels)]

    fig, ax = plt.subplots(figsize=(6, 6))
    wedges, texts, autotexts = ax.pie(
        values, labels=labels, autopct="%1.0f%%", colors=colors,
        textprops={"color": "#c9d1d9", "fontsize": 12},
        wedgeprops={"edgecolor": "#0d1117", "linewidth": 2},
        startangle=90, pctdistance=0.75
    )
    for t in autotexts:
        t.set_fontweight("bold")
    ax.set_title("Language Usage", fontsize=14, fontweight="bold", pad=20)

    plt.tight_layout()
    fig.savefig(ASSETS / "language_pie.png")
    plt.close(fig)
    print("  ✅ language_pie.png")


def generate_all_charts(stats):
    """Generate all charts."""
    setup_style()
    chart_difficulty(stats)
    chart_topics(stats)
    chart_rating_progression(stats)
    chart_heatmap(stats)
    chart_monthly(stats)
    chart_language(stats)


# ─── README Generator ────────────────────────────────────────────────────────
def generate_readme(solutions, stats):
    """Generate a beautiful README.md."""
    now = datetime.now().strftime("%B %d, %Y at %I:%M %p")
    ui = stats.get("user_info")
    total = stats["total"]
    matched = stats["matched_count"]

    # Rating color for header badge
    rating = ui["rating"] if ui else 0
    if rating >= 2400: rank_color = "red"
    elif rating >= 2100: rank_color = "orange"
    elif rating >= 1900: rank_color = "red"
    elif rating >= 1600: rank_color = "purple"
    elif rating >= 1400: rank_color = "blue"
    elif rating >= 1200: rank_color = "cyan"
    elif rating >= 1000: rank_color = "green"
    else: rank_color = "grey"

    lines = []
    w = lines.append

    # ── HEADER ──
    w("<!-- AUTO-GENERATED by script.py — do not edit manually -->")
    w("")
    w("<div align=\"center\">")
    w("")
    w("# ⚔️ Codeforces Solutions")
    w("")
    if ui:
        w(f"![Rating](https://img.shields.io/badge/Rating-{ui['rating']}-{rank_color}?style=for-the-badge&logo=codeforces)")
        w(f"![Max Rating](https://img.shields.io/badge/Max-{ui['max_rating']}-gold?style=for-the-badge&logo=codeforces)")
    w(f"![Problems Solved](https://img.shields.io/badge/Solved-{total}-brightgreen?style=for-the-badge)")
    w(f"![Contest Solves](https://img.shields.io/badge/Contests-{stats['contest_solves']}-blueviolet?style=for-the-badge)")
    if stats["longest_streak"] > 0:
        w(f"![Streak](https://img.shields.io/badge/Streak-{stats['current_streak']}-🔥-orange?style=for-the-badge)")
    w(f"![Language](https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=cplusplus)")
    w("")
    w(f"<sub>Auto-updated on {now}</sub>")
    w("")
    w("</div>")
    w("")
    w("---")
    w("")

    # ── STATS CARDS ──
    w("## 📊 Statistics at a Glance")
    w("")
    w("<div align=\"center\">")
    w("")
    w("| 🎯 Total Solved | 🏷️ Topics | 🏆 Matched to CF | 🏁 Contests | 📅 Active Days |")
    w("|:---:|:---:|:---:|:---:|:---:|")
    topics_count = len(stats.get("tag_dist", {})) or len(stats.get("topic_dist", {}))
    active_days = len(stats.get("solve_dates", []))
    w(f"| **{total}** | **{topics_count}** | **{matched}/{total}** | **{stats['contest_solves']}** | **{active_days}** |")
    w("")
    w("</div>")
    w("")

    # ── STREAKS ──
    if stats["current_streak"] > 0 or stats["longest_streak"] > 0:
        w("### 🔥 Streaks")
        w("")
        w(f"| 🔥 Current Streak | 🏆 Longest Streak | 📆 First Solve | 📅 Latest Solve |")
        w(f"|:---:|:---:|:---:|:---:|")
        first = stats["first_solve"].strftime("%b %d, %Y") if stats["first_solve"] else "N/A"
        last = stats["last_solve"].strftime("%b %d, %Y") if stats["last_solve"] else "N/A"
        w(f"| **{stats['current_streak']} days** | **{stats['longest_streak']} days** | {first} | {last} |")
        w("")

    # ── USER INFO ──
    if ui:
        w("### 👤 Codeforces Profile")
        w("")
        w(f"<div align=\"center\">")
        w("")
        w(f"| 📊 Current Rating | 🏆 Max Rating | 🎖️ Rank | 👑 Max Rank |")
        w(f"|:---:|:---:|:---:|:---:|")
        w(f"| **{ui['rating']}** | **{ui['max_rating']}** | {ui['rank'].title()} | {ui['max_rank'].title()} |")
        w("")
        w("</div>")
        w("")

    # ── RATING PROGRESSION ──
    if (ASSETS / "rating_chart.png").exists():
        w("### 📈 Rating Progression")
        w("")
        w("<div align=\"center\">")
        w("")
        w("![Rating Progression](assets/rating_chart.png)")
        w("")
        w("</div>")
        w("")

    # ── DIFFICULTY DISTRIBUTION ──
    if (ASSETS / "difficulty_dist.png").exists():
        w("### 📊 Difficulty Distribution")
        w("")
        w("<div align=\"center\">")
        w("")
        w("![Difficulty Distribution](assets/difficulty_dist.png)")
        w("")
        w("</div>")
        w("")
        w("| Bucket | Count | Bar |")
        w("|:---|:---:|:---|")
        for label, count in stats.get("buckets", {}).items():
            bar_len = min(count, 30)
            bar = "█" * bar_len + "░" * max(0, 20 - bar_len)
            w(f"| {label} | **{count}** | `{bar}` |")
        w("")

    # ── TOPIC DISTRIBUTION ──
    if (ASSETS / "topic_dist.png").exists():
        w("### 🏷️ Topics & Tags")
        w("")
        w("<div align=\"center\">")
        w("")
        w("![Topic Distribution](assets/topic_dist.png)")
        w("")
        w("</div>")
        w("")

    # ── MONTHLY SOLVES ──
    if (ASSETS / "monthly_solves.png").exists():
        w("### 📅 Monthly Progress")
        w("")
        w("<div align=\"center\">")
        w("")
        w("![Monthly Solves](assets/monthly_solves.png)")
        w("")
        w("</div>")
        w("")

    # ── ACTIVITY HEATMAP ──
    if (ASSETS / "activity_heatmap.png").exists():
        w("### 🗓️ Activity Heatmap")
        w("")
        w("<div align=\"center\">")
        w("")
        w("![Activity Heatmap](assets/activity_heatmap.png)")
        w("")
        w("</div>")
        w("")

    # ── LANGUAGE PIE ──
    if (ASSETS / "language_pie.png").exists():
        w("### 💻 Languages")
        w("")
        w("<div align=\"center\">")
        w("")
        w("![Language Usage](assets/language_pie.png)")
        w("")
        w("</div>")
        w("")

    # ── HARDEST PROBLEMS ──
    if stats.get("hardest"):
        w("### 🏆 Hardest Problems Solved")
        w("")
        w("| # | Problem | Rating | Tags | Link |")
        w("|:---:|:---|:---:|:---|:---:|")
        for i, p in enumerate(stats["hardest"][:10], 1):
            tags = ", ".join(p["tags"][:3]) if p["tags"] else "—"
            medal = ["🥇", "🥈", "🥉"][i-1] if i <= 3 else f"#{i}"
            w(f"| {medal} | **{p['name']}** | `{p['rating']}` | {tags} | [🔗]({p['url']}) |")
        w("")

    # ── RECENT SOLVES ──
    recent = sorted(solutions, key=lambda s: s.get("git_date") or datetime.min, reverse=True)[:15]
    if recent:
        w("### 🕐 Recent Solves")
        w("")
        w("| Problem | Difficulty | Topic | Date | Link |")
        w("|:---|:---:|:---|:---:|:---:|")
        for s in recent:
            mp = s.get("matched_problem")
            diff = mp.get("rating", "—") if mp else (s["difficulty"] or "—")
            tag = mp.get("tags", [""])[0].title() if mp and mp.get("tags") else s["topic"]
            date_str = s["git_date"].strftime("%b %d, %Y") if s["git_date"] else "—"
            url = f"https://codeforces.com/problemset/problem/{mp['contestId']}/{mp['index']}" if mp else "#"
            icon = "🔗" if mp else "📁"
            w(f"| **{s['problem_name']}** | `{diff}` | {tag} | {date_str} | [{icon}]({url}) |")
        w("")

    # ── ALL PROBLEMS TABLE ──
    matched_solutions = sorted(solutions, key=lambda s: s.get("matched_problem", {}).get("rating", 0) if s.get("matched_problem") else 0)
    if matched_solutions:
        w("### 📋 All Solved Problems")
        w("")
        w("<details>")
        w("<summary>Click to expand full problem list</summary>")
        w("")
        w("| # | Problem | Rating | Topic | Link |")
        w("|:---:|:---|:---:|:---|:---:|")
        for i, s in enumerate(matched_solutions, 1):
            mp = s.get("matched_problem")
            diff = mp.get("rating", "—") if mp else (s["difficulty"] or "—")
            tag = mp.get("tags", [""])[0].title() if mp and mp.get("tags") else s["topic"]
            url = f"https://codeforces.com/problemset/problem/{mp['contestId']}/{mp['index']}" if mp else "#"
            icon = "🔗" if mp else "📁"
            w(f"| {i} | **{s['problem_name']}** | `{diff}` | {tag} | [{icon}]({url}) |")
        w("")
        w("</details>")
        w("")

    # ── ACHIEVEMENTS ──
    if stats.get("achievements"):
        w("### 🏅 Achievements")
        w("")
        w("<div align=\"center\">")
        w("")
        for emoji, title, desc in stats["achievements"]:
            w(f"![{title}](https://img.shields.io/badge/{emoji}-{title.replace(' ', '%20')}-success?style=for-the-badge)")
        w("")
        w("</div>")
        w("")

    # ── DIRECTORY STRUCTURE ──
    w("### 📁 Repository Structure")
    w("")
    w("```")
    w("CodeForces/")
    dirs_seen = set()
    for s in solutions:
        d = Path(s["file"]).parent
        if str(d) != "." and str(d) not in dirs_seen:
            dirs_seen.add(str(d))
            w(f"├── {d}/")
    w("```")
    w("")

    # ── FOOTER ──
    w("---")
    w("")
    w(f"<div align=\"center\">")
    w(f"")
    w(f"<sub>🤖 Auto-generated by <b>script.py</b> | Last updated: {now}</sub>")
    w(f"")
    if not ui:
        w(f"<sub>💡 Set <code>CF_HANDLE</code> secret in your repo to enable personal stats</sub>")
        w(f"")
    w(f"</div>")
    w("")

    readme = "\n".join(lines)
    (ROOT / "README.md").write_text(readme, encoding="utf-8")
    print(f"  ✅ README.md generated ({len(lines)} lines)")


# ─── Main ────────────────────────────────────────────────────────────────────
def main():
    print("=" * 60)
    print("  🔧 Codeforces Repo Generator")
    print("=" * 60)

    # 1. Scan repo
    print("\n📂 Scanning repository...")
    solutions = scan_repo()

    # 2. Fetch user info (optional)
    user_info = None
    submissions = None
    if CF_HANDLE:
        print(f"\n👤 Fetching Codeforces data for '{CF_HANDLE}'...")
        user_info = cf_get("user.info", {"handles": CF_HANDLE})
        if user_info and user_info.get("status") == "OK":
            ui = user_info["result"][0]
            print(f"  Rating: {ui.get('rating', '?')} | Max: {ui.get('maxRating', '?')} | Rank: {ui.get('rank', '?')}")
        else:
            print(f"  [WARN] Could not fetch user info for '{CF_HANDLE}'")
            user_info = None

        submissions = cf_get("user.status", {"handle": CF_HANDLE, "from": "1", "count": "10000"})
        if submissions:
            print(f"  Fetched {len(submissions.get('result', []))} submissions")

    # 3. Match problems
    print("\n🔗 Matching problems to Codeforces...")
    match_problems(solutions)

    # 4. Compute analytics
    print("\n📈 Computing analytics...")
    stats = compute_analytics(solutions, user_info, submissions)
    print(f"  Total: {stats['total']} | Matched: {stats['matched_count']} | Topics: {len(stats.get('tag_dist', {}))}")

    # 5. Generate charts
    print("\n🎨 Generating charts...")
    generate_all_charts(stats)

    # 6. Generate README
    print("\n📝 Generating README.md...")
    generate_readme(solutions, stats)

    print("\n" + "=" * 60)
    print("  ✅ Done! README and charts are ready.")
    print("=" * 60)


if __name__ == "__main__":
    main()
