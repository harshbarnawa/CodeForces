#include<bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    int temp = 0,rem;
    cin >>n;
//first i thought the logic of reminder used in reverse a num
//then i count the lucky num digit by digit them temp++
//if temp is also a lucky then Yes otherwise no
    while(n!=0){
        rem = n % 10;
        if(rem == 4 || rem == 7){

            temp++;
        }
        n /= 10;
    }
    cout << ((temp == 4 || temp == 7)?"YES":"NO");



return 0;
}