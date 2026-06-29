#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin >> n >> m;
    vector<int> a(n);

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    int ans = 0;
    for(int i = 0; i < m; i++) {
        if(a[i] < 0)
            ans += -a[i];
    }

    cout << ans;
}