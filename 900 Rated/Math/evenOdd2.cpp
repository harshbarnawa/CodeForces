#include<bits/stdc++.h>
using namespace std;

int main() {
    long long n, k;
    cin>>n>>k;
    long long odd = (n + 1) / 2; //just counting odds

    if(k<= odd){
        cout << (2 * k) - 1; //left part of arr
    } else{
        cout << 2 * (k - odd); //even part
    }


    return 0;
}