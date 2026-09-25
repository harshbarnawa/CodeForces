#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;

    while(t--){
        int n;
        cin>>n;

        int e=0,o=0;

        for(int i=0;i<n;i++){
            int x;
            cin>>x;

            if(x%2==0) e+=x;
            else o+=x;
        }

        if(e>o) cout<<"YES\n";
        else cout<<"NO\n";
    }

    return 0;
}