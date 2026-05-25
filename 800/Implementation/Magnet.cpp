#include<bits/stdc++.h>
using namespace std;

int main() {
    int n,curr,ct = 1,prev;
    cin>>n;
    cin>>prev;
    while(--n){
        cin>>curr;
        if(curr != prev){
            ct++;
        }

        prev = curr;
      

       }
    
    cout << ct;
}