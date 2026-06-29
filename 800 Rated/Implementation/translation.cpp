#include<bits/stdc++.h>
using namespace std;

int main() {
    string s,t;
    cin >> s>>t;
//just reversed string 2 and compared it if equal then yes
    reverse(t.begin(), t.end());
    
    cout << (s==t?"YES": "NO");

    
    
}