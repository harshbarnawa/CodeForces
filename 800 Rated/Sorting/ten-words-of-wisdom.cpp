#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int ans=0,mx=0;
        
        for(int i=1;i<=n;i++){
            int a,b;
            cin>>a>>b;
            if(a<=10 && b>mx){
                mx=b;
                ans=i;
            }
        }
        
        cout<<ans<<"\n";
    }
}