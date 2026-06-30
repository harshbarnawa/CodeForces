#include<bits/stdc++.h>
using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int x;
        cin >> x;

        long long y = 11;
        while(y <= x){
        y = (y * 10) - 9; //11, 101, 1001 idea
        }

        cout << y << '\n';
    }

    return 0;
}