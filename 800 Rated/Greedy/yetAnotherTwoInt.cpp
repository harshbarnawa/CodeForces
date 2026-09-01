#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        long long a, b;
        cin >> a >> b;

        long long diff = abs(a - b);
        cout << (diff + 9) / 10 << '\n';
    }

    return 0;
}