#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, k,ct =0;
    cin>>n>>k;
    vector<int> arr;
    for(int i = 1;i <= n;i++){
        if(i%2!=0){
            arr.push_back(i);
        }
    }
    for(int i = 1;i <= n;i++){
        if(i%2==0){
            arr.push_back(i);
        }
    }
    cout << arr[k - 1];

}