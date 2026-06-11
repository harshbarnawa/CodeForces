#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);

        for (int &x : a)
            cin >> x;

        sort(a.begin(), a.end());

        vector<int> b, c;

        int mn = a[0];

        for(int x : a){
            if (x == mn)
                b.push_back(x);
            else
                c.push_back(x);
        }

        if(c.empty()) {
            cout << -1 << '\n';
            continue;
        }

        cout << b.size()<< ' ' << c.size() << '\n';

        for(int x : b)
            cout << x << ' ';
        cout << '\n';

        for(int x : c)
            cout << x << ' ';
        cout << '\n';
    }
}