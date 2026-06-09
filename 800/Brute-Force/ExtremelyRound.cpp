#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   int t;
   cin>>t;

   while(t--){
    string s;
    cin >> s;

    //ex 42 so size-1 like (2 - 1) * 9
    //s[0] - '0' = 4 hence 9+4 13
        cout << (s.size() - 1) * 9 + (s[0] - '0') << '\n'; 


   }
}