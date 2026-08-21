#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n;
        string s;
        cin >> n >> s;

        long long dp[2] = {0, 0};

        for(int x = 0; x < 2; x++){
            if(s[0] == '?' || s[0] - '0' == x)
                dp[x] = 1;
        }

        for(int i = 1; i < n; i++){
            long long ndp[2] = {0, 0};

            for(int prev = 0; prev < 2; prev++){
                for(int cur = 0; cur < 2; cur++){
                    if(s[i] != '?' && s[i] - '0' != cur)
                        continue;

                    if(i == 1 || (prev + cur) != (s[i-2] == '?' ? -1 : 0)){
                    }
                }
            }
        }

        if(n == 2){
            int ans = 1;
            for(char c : s)
                if(c == '?') ans *= 2;
            cout << ans << '\n';
            continue;
        }

        long long dp2[2][2] = {};

        for(int a = 0; a < 2; a++){
            if(s[0] != '?' && s[0] - '0' != a) continue;

            for(int b = 0; b < 2; b++){
                if(s[1] != '?' && s[1] - '0' != b) continue;
                dp2[a][b] = 1;
            }
        }

        for(int i = 2; i < n; i++){
            long long ndp[2][2] = {};

            for(int a = 0; a < 2; a++){
                for(int b = 0; b < 2; b++){
                    if(dp2[a][b] == 0) continue;

                    for(int c = 0; c < 2; c++){
                        if(s[i] != '?' && s[i] - '0' != c) continue;

                        if(a + b != b + c){
                            ndp[b][c] = (ndp[b][c] + dp2[a][b]) % 998244353;
                        }
                    }
                }
            }

            memcpy(dp2, ndp, sizeof(dp2));
        }

        long long ans = 0;

        for(int a = 0; a < 2; a++){
            for(int b = 0; b < 2; b++){
                ans = (ans + dp2[a][b]) % 998244353;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}