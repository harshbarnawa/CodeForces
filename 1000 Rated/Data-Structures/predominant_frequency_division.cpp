#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int>a(n),p(n),q(n);

        for(int i=0;i<n;i++){
            cin>>a[i];
            p[i]=(a[i]==1?1:-1)+(i?p[i-1]:0);
            q[i]=(a[i]==3?-1:1)+(i?q[i-1]:0);
        }

        int mn=1e9;
        bool ok=false;

        for(int j=1;j<n-1;j++){
            if(p[j-1]>=0) mn=min(mn,q[j-1]);
            if(mn<=q[j]){
                ok=true;
                break;
            }
        }

        cout<<(ok?"YES":"NO")<<'\n';
    }
}