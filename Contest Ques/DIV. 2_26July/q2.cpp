#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n, k;
        cin >> n >> k;

        int runs = n - k;

        int cnt0 = n / 2;
        int cnt1 = n - cnt0;

        string ans = "-1";

        for(int st = 0; st < 2; st++){
            int r0, r1;

            if(st == 0){
                r0 = (runs + 1) / 2;
                r1 = runs / 2;
            }else{
                r0 = runs / 2;
                r1 = (runs + 1) / 2;
            }

            if(r0 > cnt0 || r1 > cnt1) continue;
            if((r0 == 0 && cnt0 > 0) || (r1 == 0 && cnt1 > 0)) continue;

            vector<int> len0(r0, 1), len1(r1, 1);

            if(r0) len0[0] += cnt0 - r0;
            if(r1) len1[0] += cnt1 - r1;

            string s;
            int i0 = 0, i1 = 0;
            int cur = st;

            while(i0 < r0 || i1 < r1){
                if(cur == 0){
                    s.append(len0[i0], '0');
                    i0++;
                }else{
                    s.append(len1[i1], '1');
                    i1++;
                }
                cur ^= 1;
            }

            ans = s;
            break;
        }

        cout << ans << '\n';
    }

    return 0;
}