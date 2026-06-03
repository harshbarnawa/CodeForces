#include <bits/stdc++.h>
using namespace std;

int main() {
    int a,b;
    cin>>a>>b;

    int pair1 = 0;
    int pair2 = 0;

    while(a>0 && b > 0){
        pair1++;  //pairs of diff socks
        a--;
        b--;
    }
    if(a > 0){
        pair2 = a/2; //remaining same socks pair
    } else {
        pair2 = b/2;
    }
    cout << pair1 << " " << pair2;

    return 0;
}