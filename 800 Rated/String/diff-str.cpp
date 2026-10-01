#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        string s;
        cin >> s;

        string r = s;
        sort(r.begin(), r.end());

        if(r == s){
            reverse(r.begin(), r.end());
        }

        if(r == s){
            cout << "NO\n";
        }else{
            cout << "YES\n";
            cout << r << '\n';
        }
    }

    return 0;
}