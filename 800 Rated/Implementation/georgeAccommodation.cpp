#include <bits/stdc++.h>
using namespace std;

int main() {
    //no of people in room = p
    //capicity = q
    int n,p,q, ct = 0;
    cin >>n;

    while(n--){
        cin>>p>>q;
        if(q-p>=2){
            ct++;
        }
    }
    cout << ct;


    return 0;
}