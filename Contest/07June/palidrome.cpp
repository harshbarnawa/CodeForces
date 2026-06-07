#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    
    while(t--){
    long long n;
    cin >> n;

    if(n == 10){
        cout << -1 << '\n';
        continue;

    }
    long long r = n % 12;
    long long a;

    if(r <= 9){
        a = r;
    }   else if(r == 10){
        a = 22;
    } else{
        a = 11;
    }

    cout << a<< ' '<< n - a << '\n';
   
 }


}