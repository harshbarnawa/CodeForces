#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;


    while(t--){
        int n;
        cin>>n;

        vector<int> v(n);
       unordered_map<int, int> freq;

       for(int i = 0;i < n;i++){
        cin>> v[i];
        freq[v[i]]++;
       }

       for(int i = 0;i < n;i++){
        if(freq[v[i]] == 1){
            cout << i + 1 << "\n";
            break;
        }
       }


    }
}