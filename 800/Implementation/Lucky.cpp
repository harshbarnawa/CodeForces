#include<bits/stdc++.h>
using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    
    while(t--){
    string s;
    cin>>s;
        int sum1 = 0;
        int sum2 = 0;
    for(char c : s){
        sum1 += (c - '0');
    }
    for(int i = 0;i<s.length()/2;i++){
        sum2 += (s[i] - '0');
    }

    cout << ((sum1/2)==sum2?"YES\n":"NO\n");
  }

    return 0;
 }