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
        int l = 0;
        long long r = 0;
        //r - 1 + 1
        //n = 5, 5 + 1 + 1 = 7,
        //n = 5, 1 + 1n = 5 
        //r - l + 1 or l //r addition //l numbers
        vector<int> b(n);      

    for(int i = 0; i < n; i++) {
        cin >> b[i];   
        r+= b[i];  
        
        if(b[i]>0){
            l++;
        }
    }
    cout << min((long long)l, r - n + 1) << '\n';  
  }
  
    return 0;
 }