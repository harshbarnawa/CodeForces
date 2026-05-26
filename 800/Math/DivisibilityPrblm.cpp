#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;

    while(t--){
        int a,b,ct=0;
        cin>>a>>b;
        cout<<(b - a % b) % b <<endl;
    }
    return 0;
}