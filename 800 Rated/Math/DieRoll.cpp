#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int y,w;
    cin>>y>>w;

    int mx=max(y,w);
    int a=7-mx,b=6;
    int g=__gcd(a,b);

    cout<<a/g<<"/"<<b/g;

    return 0;
}