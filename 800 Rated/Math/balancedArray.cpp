#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        int half = n / 2;

        if (half % 2) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";

        long long evenSum = 0, oddSum = 0;

        for (int i = 1; i <= half; i++) {
            cout << 2 * i << " ";
            evenSum += 2 * i;
        }

        for (int i = 1; i < half; i++) {
            cout << 2 * i - 1 << " ";
            oddSum += 2 * i - 1;
        }

        cout << evenSum - oddSum << "\n";
    }

    return 0;
}