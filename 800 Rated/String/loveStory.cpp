#include<bits/stdc++.h>
using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    
    while(t--){
    string s;
    string c = "codeforces";
    cin>>s;
        int ct = 0;
    for(int i = 0;i < s.length();i++){
        if(s[i]!=c[i]){
            ct++;
        }
    }
    
    cout << ct << "\n";
  }

    return 0;
 }