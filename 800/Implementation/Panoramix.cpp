#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> p = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};

    for (int i = 0; i < p.size() - 1; i++) {
        if (p[i] == n) {
            cout << (p[i + 1] == m ? "YES" : "NO");
            break;
        }
    }
}