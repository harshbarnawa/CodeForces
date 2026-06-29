#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>> t;

    while(t--){
        int n, c;
        cin>>n>>c;
int s1 = 0, s2 = 0;
        bool ok = true;
        int cur = 0;
        int ans = INT_MAX;
        vector<int> a(n), b(n);
        vector<int> x, y;
        for(int i = 0;i < n;i++){
            cin >> a[i];
            s1 +=a[i];
        }
        for(int i = 0;i < n;i++){
            cin >> b[i];
            s2 +=b[i];
        }
    
        //Reorder nahi krnaa
        for(int i = 0;i < n;i++){
            if(a[i] < b[i]){
                ok = false;
            }
            cur += a[i] - b[i]; //total mins
        }
        if(ok){
            ans = cur;
        }
        x = a;
        y = b;

        sort(x.begin(),x.end());
        sort(y.begin(),y.end());

        ok = true;

        for(int i = 0;i < n;i++){
            if(x[i] < y[i]){
                ok = false;
            }
        }

        if(ok){ //c + mins
            ans = min(ans, c + s1 - s2);
        }

        if(ans == INT_MAX){
            cout << -1 << "\n";
        } else{
            cout << ans << "\n";
        }
    }
}