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

    vector<int> v(n);      
    int ct =0;
    for(int i = 0; i < n; i++) {
        cin >> v[i];  
        if(v[i]==2){
        ct++;     
        }
    }  
    if(ct % 2){
        cout << -1 << "\n";
        continue;
    }

    int req = ct /2;
    int two = 0;

    for(int i = 0; i < n;i++){
        if(v[i] == 2){
            two++;
        }
        if(two == req){
            cout << i + 1 << '\n';
            break;
        }
    }
    

  }

    return 0;
 }