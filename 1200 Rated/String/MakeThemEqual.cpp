#include<bits/stdc++.h>
using namespace std;

#define int long long

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin>>t;

    while(t--){
        int n;
        char c;
        cin>>n>>c;

        string s;
        cin>>s;

        bool ok = true;
        for(char ch : s){
            if(ch != c){
                ok = false;
                break;
            }
        }
        if(ok){
            cout<<0<<"\n";
            continue;
        }

        bool found = false;

        for(int x = 1;x <= n;x++){
            bool good = true;

            for(int j = x;j <= n;j += x){
                if(s[j - 1] != c){
                    good = false;
                    break;
                }
            }

            if(good){
                cout<<1<<"\n";
                cout<<x<<"\n";
                found = true;
                break;
            }
        }


        
        if(!found){
            cout<<2<<"\n";
            cout<<n<<" "<<n - 1<<"\n";
        }
    }

    return 0;
}