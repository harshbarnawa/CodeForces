#include<bits/stdc++.h>
using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n, ct = 1;
        cin >> n;

        string s;
        cin >> s;

    for(int i = 1;i < n;i++){
        if(s[i] != s[i - 1]){
            ct++;
        }
    }

    cout << (ct == 2? 2 : 1) <<'\n';

    }

    return 0;
}