#include<bits/stdc++.h>
using namespace std;


int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    
    while(t--){
    int n,k;
    cin >> n>>k;
    bool isD = false;
    vector<int> v(n);      
    for(int i = 0; i < n; i++) {
        cin >> v[i];       
    }  

    for(int i : v){
        if(i == k){
            isD = true;
        }
    }

    cout << (isD?"YES\n":"NO\n");


  }

    return 0;
 }