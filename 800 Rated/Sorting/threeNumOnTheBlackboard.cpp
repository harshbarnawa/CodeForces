#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        long long a,b,c;
        cin >> a >> b >> c;

        vector<long long> v={a,b,c};
        sort(v.begin(),v.end());

        cout << min(v[2]-v[0],v[1]) << '\n';
    }

    return 0;
}