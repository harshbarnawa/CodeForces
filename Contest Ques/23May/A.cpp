#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>> t;

    while(t--){
        int n;
        cin >> n;

        vector<int> a(n);

        for(int i = 0;i < n; i++){
            cin >> a[i];
        }

        sort(a.begin(), a.end());

        int mn = a[0];
        int mx = a[n - 1];

        cout << (mx - mn + 1) / 2<<endl;
    }

    return 0;
}