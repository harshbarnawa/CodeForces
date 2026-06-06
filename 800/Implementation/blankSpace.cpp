#include<bits/stdc++.h>
using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    
     while(t--){
        int n, x, ct = 0, ans = 0;
        cin >> n;

        while(n--){
            cin>> x;

            if(x == 0){
                ct++;
                ans = max(ans, ct);
            }else{
                ct = 0;
            }
        }
        //maximum consecutive zeross
        cout << ans << '\n';
    }
}