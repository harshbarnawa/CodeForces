#include<iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin>>t;

    while(t--){
        int n,m;
        cin>>n>>m;
        string x ,s;
        cin>>x>>s;
          int ans = -1;
              for (int i = 0; i <= 6; i++) {
            if (x.find(s) != string::npos) {
                ans = i;
                break;
            }
            x += x;
        }

        cout << ans << '\n';
    }
    }
