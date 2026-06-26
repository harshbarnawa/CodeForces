#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while(t--) {
        int n, neg = 0;
        cin >> n;

        for(int i = 0; i < n; i++){
            int x;
            cin >> x;
            if (x == -1) neg++;
        }

        int sum = n - 2 * neg;   //pos - neg
        int ans = 0;

        if(sum < 0){
            ans = (-sum + 1) / 2;
            neg -= ans;
        }

        if(neg % 2){ 
            ans++;
        }
        cout << ans << endl;
    }
}