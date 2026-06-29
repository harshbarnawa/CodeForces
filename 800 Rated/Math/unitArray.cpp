#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--){
        int n;
        cin >> n;

        int ct = 0, ans = 0;

        for(int i = 0; i < n; i++){
            int x;
            cin >> x;
            if (x == -1) ct++;
        }


        while(2 * ct > n){
            ct--;
            ans++;
        }

        if(ct % 2){
            ans++;
        }
        cout<< ans << '\n';
    }

    return 0;
}