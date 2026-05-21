#include <bits/stdc++.h>
using namespace std;

int main() {
    //Bear w*3 every year
    //bear2 w*2 every yr
    //if b1 > b2 yr++
    //if b1=b2 then return 1 yr
    //
    int b1, b2,yr = 0;
    cin >>b1>>b2;
    while(b1<=b2){
        b1 = b1*3;
        b2 = b2*2;
        yr++;
    }
    cout << yr;


    return 0;
}