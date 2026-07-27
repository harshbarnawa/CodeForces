#!/usr/bin/env python3
"""
script.py — Auto-generate README.md for CodeForces repository.

Scans the repository structure and generates a minimal, clean README.
Runs in under 1 second. No external dependencies.
"""

import os
import glob
import subprocess
from datetime import datetime

# ─── Configuration ───────────────────────────────────────────────────────────

REPO_ROOT = os.path.dirname(os.path.abspath(__file__))
REPO_NAME = "CodeForces"
REPO_DESC = "Competitive Programming Solutions on CodeForces"
GITHUB_USER = "harshbarnawa"

# Folders that represent rating groups (order matters)
RATING_FOLDERS = [
    ("800", "800 Rated"),
    ("900", "900 Rated"),
    ("1000", "1000"),
    ("1100", None),       # placeholder — exists in display
    ("1200", "1200 Rated"),
    ("1300", None),
    ("1400", None),
]

# Maximum progress bar width (terminal-style)
BAR_WIDTH = 20

# ─── Helpers ─────────────────────────────────────────────────────────────────


def count_cpp(directory):
    """Return number of .cpp files inside *directory* (recursive)."""
    if not directory or not os.path.isdir(directory):
        return 0
    return len(glob.glob(os.path.join(directory, "**", "*.cpp"), recursive=True))


def get_last_commit_info():
    """Return (short_hash, date_str) of the most recent commit."""
    try:
        result = subprocess.run(
            ["git", "log", "-1", "--format=%h|%ai"],
            capture_output=True, text=True, cwd=REPO_ROOT, timeout=5,
        )
        parts = result.stdout.strip().split("|")
        if len(parts) == 2:
            return parts[0], parts[1].split()[0]
    except Exception:
        pass
    return "HEAD", datetime.now().strftime("%Y-%m-%d")


def get_stars_forks():
    """Return (stars, forks) from GitHub API if available, else (0, 0)."""
    import urllib.request
    import json
    try:
        url = f"https://api.github.com/repos/{GITHUB_USER}/{REPO_NAME}"
        req = urllib.request.Request(url, headers={"User-Agent": "script.py"})
        with urllib.request.urlopen(req, timeout=5) as resp:
            data = json.loads(resp.read().decode())
            return data.get("stargazers_count", 0), data.get("forks_count", 0)
    except Exception:
        return 0, 0


# ─── Section generators ─────────────────────────────────────────────────────


def _stars_str(rating):
    """Return difficulty stars: 800→★☆☆☆☆, 900→★★☆☆☆, ..., 1200+→★★★★★"""
    if not rating.isdigit():
        return "☆☆☆☆☆"
    level = (int(rating) - 800) // 100 + 1
    level = max(1, min(5, level))
    return "★" * level + "☆" * (5 - level)


def _progress_bar(count, maximum):
    """Return a terminal-style progress bar string."""
    if maximum == 0:
        return "░" * BAR_WIDTH
    filled = int(round((count / maximum) * BAR_WIDTH))
    filled = max(0, min(filled, BAR_WIDTH))
    return "█" * filled + "░" * (BAR_WIDTH - filled)


MAX_EXPECTED = 120  # used for progress-bar scaling (800-lvl has ~115)


def build_progress_table(rating_data):
    """Build the ASCII progress table inside a code block."""
    lines = ["```text"]
    lines.append(f"{'Rating':<10} {'Solved':<8} Progress")
    lines.append("─" * 50)
    total = 0
    for rating_label, count in rating_data:
        total += count
        stars = _stars_str(rating_label)
        if count == 0:
            lines.append(f"{rating_label:<10} {stars:<8} Work in progress")
        else:
            bar = _progress_bar(count, MAX_EXPECTED)
            lines.append(f"{rating_label:<10} {stars:<8} {count:<5} {bar}")
    lines.append("─" * 50)
    lines.append(f"{'TOTAL':<23} {total} solutions")
    lines.append("```")
    return "\n".join(lines)


def build_tree():
    """Build the repository structure tree (shallow — root level only)."""
    lines = ["```text", f"{REPO_NAME}/"]

    IGNORE = {".git", ".claude", "assets", "__pycache__", ".github"}
    dirs = sorted(
        e for e in os.listdir(REPO_ROOT)
        if os.path.isdir(os.path.join(REPO_ROOT, e))
        and not e.startswith(("."))
        and e not in IGNORE
    )
    files = sorted(
        e for e in os.listdir(REPO_ROOT)
        if os.path.isfile(os.path.join(REPO_ROOT, e))
        and e.endswith((".cpp"))
    )

    items = []
    for d in dirs:
        c = count_cpp(os.path.join(REPO_ROOT, d))
        # Clean up names for display
        name = d
        if "Rated" in d or d == "1000":
            name = name.replace("Rated", "Rated Problems")
            if d == "1000":
                name = "1000_Rated Problems"
        suffix = f"    # {c} solutions" if c > 0 else ""
        items.append(("📂 " + name + suffix, True))
    for f in files:
        items.append(("📄 " + f, False))

    for i, (label, _) in enumerate(items):
        connector = "└── " if i == len(items) - 1 else "├── "
        lines.append(connector + label)
    lines.append("```")
    return "\n".join(lines)


def build_topics_table(topic_data):
    """Build a small markdown table of topics -> solved count."""
    if not topic_data:
        return ""
    # Sort descending by count
    sorted_topics = sorted(topic_data.items(), key=lambda x: -x[1])
    lines = []
    lines.append("| Topic               | Solved |")
    lines.append("| ------------------- | -----: |")
    for topic, count in sorted_topics:
        lines.append(f"| {topic:<19} | {count:>6} |")
    return "\n".join(lines)


def build_header(stars, forks, commit_hash, commit_date):
    """Build the README header."""
    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S %Z")
    # Remove timezone offset trailing
    now = datetime.now().strftime("%Y-%m-%d %H:%M")

    badge_url = "https://img.shields.io/badge"
    badges = (
        f"[![Stars]({badge_url}/stars-{stars}-brightgreen)](https://github.com/{GITHUB_USER}/{REPO_NAME}) "
        f"[![Forks]({badge_url}/forks-{forks}-blue)](https://github.com/{GITHUB_USER}/{REPO_NAME}/fork) "
        f"[![Last Commit]({badge_url}/last_commit-{commit_date}-orange)](https://github.com/{GITHUB_USER}/{REPO_NAME}/commits/main) "
        f"[![C++]({badge_url}/C%2B%2B-00599C?logo=c%2B%2B)](https://github.com/{GITHUB_USER}/{REPO_NAME})"
    )

    return (
        f"<div align='center'>\n\n"
        f"# {REPO_NAME}\n\n"
        f"*{REPO_DESC}*\n\n"
        f"{badges}\n\n"
        f"**Last Updated:** {now}\n\n"
        f"</div>\n"
    )


# ─── Data collection ────────────────────────────────────────────────────────


def collect_rating_data():
    """Scan folders and return list of (rating_label, count)."""
    data = []
    for label, folder in RATING_FOLDERS:
        if folder:
            path = os.path.join(REPO_ROOT, folder)
            data.append((label, count_cpp(path)))
        else:
            data.append((label, 0))
    return data


TOPIC_NORMALIZE = {
    "Brute-Force": "Brute Force",
    "Dynamic-Programming": "DP",
    "Implemention": "Implementation",
    "math": "Math",
    "games": "Games",
    "greedy": "Greedy",
}


def collect_topic_data():
    """Aggregate .cpp counts per topic folder across all rating dirs."""
    topics = {}
    for folder in RATING_FOLDERS:
        _, dirname = folder
        if dirname is None:
            continue
        path = os.path.join(REPO_ROOT, dirname)
        if not os.path.isdir(path):
            continue
        for entry in os.listdir(path):
            topic_path = os.path.join(path, entry)
            if os.path.isdir(topic_path):
                topic_name = TOPIC_NORMALIZE.get(entry, entry)
                topics[topic_name] = topics.get(topic_name, 0) + count_cpp(topic_path)
    return topics


# ─── README assembly ────────────────────────────────────────────────────────


def fast_io_template():
    return """```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        // your code here
    }
    return 0;
}
```"""


def build_readme():
    stars, forks = get_stars_forks()
    commit_hash, commit_date = get_last_commit_info()

    rating_data = collect_rating_data()
    topic_data = collect_topic_data()

    sections = []

    # 1. Header
    sections.append(build_header(stars, forks, commit_hash, commit_date))

    # 2. Progress
    sections.append("## Progress\n")
    sections.append(build_progress_table(rating_data))

    # 3. Repository Structure
    sections.append("\n## Repository Structure\n")
    sections.append(build_tree())

    # 4. Fast I/O Template
    sections.append("\n## Fast I/O Template\n")
    sections.append(fast_io_template())

    # 5. Topics Covered
    if topic_data:
        sections.append("\n## Topics Covered\n")
        sections.append(build_topics_table(topic_data))

    # 6. Compile & Run
    sections.append("\n## Compile & Run\n")
    sections.append("```bash\ng++ -std=c++17 -O2 solution.cpp -o solution && ./solution\n```")

    # 7. Footer
    now = datetime.now().strftime("%Y-%m-%d %H:%M")
    sections.append("\n---\n")
    sections.append(f"*Auto-generated by [script.py](script.py) — Last updated: {now}*")

    return "\n\n".join(sections) + "\n"


# ─── Main ────────────────────────────────────────────────────────────────────


def main():
    readme = build_readme()
    readme_path = os.path.join(REPO_ROOT, "README.md")
    with open(readme_path, "w", encoding="utf-8") as f:
        f.write(readme)
    print(f"README.md regenerated at {readme_path}")


if __name__ == "__main__":
    main()
