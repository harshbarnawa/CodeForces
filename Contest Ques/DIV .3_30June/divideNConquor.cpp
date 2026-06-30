#include<bits/stdc++.h>
using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int x,y;
        cin>>x>>y;
//if divides so x can == y
        cout <<((x % y== 0)? "YES\n": "NO\n");
    }

    return 0;
}