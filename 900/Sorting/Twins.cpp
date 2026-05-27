#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;

    vector<int> arr(n);

    int sum = 0;

    for(int i = 0; i < n; i++){ //adding all
        cin>>arr[i];
        sum += arr[i];
    }

    sort(arr.begin(), arr.end()); //sorting

    int me = 0;
    int count = 0;

    for(int i = n - 1; i >= 0; i--){ //reverse traversing

        me += arr[i];
        sum -= arr[i]; //remaining sum
        count++;

        if(me > sum){
            break;
        }
    }

    cout << count;
}