#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin>>t;

    while(t--){
        string s;
        cin>>s;

        int ct=0;
        string target="abc";

        for(int i=0;i<3;i++){
            if(s[i]!=target[i]) ct++;
        }

        cout<<(ct<=2 ? "YES" : "NO")<<"\n";
    }

    return 0;
}