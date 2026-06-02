#include<bits/stdc++.h>
using namespace std;


int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    
    while(t--){
    int n;
    cin >> n;
        bool isDif = true;
    vector<int> v(n);      
    for(int i = 0; i < n; i++) {
        cin >> v[i];       
    }  


    sort(v.begin(), v.end());

    for(int i = 0;i < n - 1; i++){
        if(v[i + 1] - v[i]>1){
            isDif = false;
            break;
        }
    }

    cout << (isDif?"YES\n":"NO\n");

  }

    return 0;
 }