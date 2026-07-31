#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k,r;
    cin>>k>>r;

    int n=1;
    while(true){
        int x=(n*k)%10;
        if(x==0||x==r){
            cout<<n;
            break;
        }
        n++;
    }
}