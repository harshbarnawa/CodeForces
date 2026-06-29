#include <bits/stdc++.h>
using namespace std;

int main() {
    int sum = 0;
    int arr[4];
    string s;

    for(int i = 0;i < 4;i++){
        cin>>arr[i];
    }

    cin >> s;
    for(char c : s){
        //just doing implicit type casting
        sum += arr[(c - '0') - 1];
    }
    cout << sum;
    return 0;
}