#include<bits/stdc++.h>
using namespace std;

int main() {
    int n,ct = 0;
    cin >>n;

    for(int i = 0;i < n;i++){
        int petya, vasya, tonya;
        cin>> petya>> vasya>> tonya;
    
    if (petya+vasya+tonya>1){
        ct++;
    }
    }
    cout <<ct;

    return 0;
}