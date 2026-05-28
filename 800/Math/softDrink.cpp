#include<bits/stdc++.h>
using namespace std;

int main() {
    int n,k,l,c,d,p,nl,np,toast,limes,salt;
    cin>>n>>k>>l>>c>>d>>p>>nl>>np;
//Note helped me to solve this
    toast = (k * l)/nl;
    limes = c * d;
    salt = p/np;
    cout << min({toast,limes,salt})/n;

    return 0;
}