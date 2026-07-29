#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;

        bool vis[26] = {};
        int ans = 0;

        for(char c : s){
            ans++;
            if(!vis[c - 'A']){
                ans++;
                vis[c - 'A'] = true;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}