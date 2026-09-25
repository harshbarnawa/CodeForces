#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        long long m,a,b,c;
        cin >> m >> a >> b >> c;

        long long x=min(a,m);
        long long y=min(b,m);

        long long rem=(m-x)+(m-y);

        cout << x+y+min(c,rem) << '\n';
    }
}