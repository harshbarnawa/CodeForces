#include<bits/stdc++.h>
using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    
    vector<int> v;
    for(int i = 1;v.size() < 1000;i++){
         if (i % 3 != 0 && i % 10 != 3) {
            v.push_back(i);
        }
    }
    while(t--){
    int k;
    cin >> k;

    cout << v[k - 1]<< "\n";
  }

    return 0;
 }