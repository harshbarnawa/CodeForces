#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;

    while(t--){
        string s;
        cin>>s;

        if(s.size()>=3 && s[0]=='1' && s[1]=='0' && s[2]!='0' && s.substr(2)!="1")
            cout<<"YES ";
        else
            cout<<"NO ";
    }

    return 0;
}