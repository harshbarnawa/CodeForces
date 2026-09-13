#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while(t--) {
        string s;
        cin >> s;

        int zero = 0, one = 0;
        for(char c : s){ //zero ones countinggg
            if(c == '0') {
                zero++;
            } else one++;
        }

        int n = s.size();
        int ans = 0;

        for(int i = 0; i < n; i++) {
            if(s[i] == '0') { //checking 1
                if(one > 0) {
                    one--;
                }else {
                    ans = n - i; //matching with 0
                    break;
                }
            }
            else{
                if(zero > 0) {
                    zero--;
                } else {
                    ans = n - i;
                    break;
                }
            }
        }

        cout << ans << "\n"; //unmatched part
    }

    return 0;
}