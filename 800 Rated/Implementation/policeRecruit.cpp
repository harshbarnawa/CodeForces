#include<bits/stdc++.h>
using namespace std;

int main() {
    int n,p=0,u=0;
    cin>>n;

    while(n--){
        int x;
        cin>>x;

        if(x==-1){
            if(p>0){
                p--;
            } else{ u++;}
        } else{
            p+=x;
        }
    }
    cout <<u;
}