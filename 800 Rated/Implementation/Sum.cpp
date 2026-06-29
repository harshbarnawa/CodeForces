#include <bits/stdc++.h>
using namespace std;
//if sum of these vars are eq to twice of largest then yess 1+4+3=2*4 
int main() {
    int t, a, b, c;
    cin >> t;

    while (t--) {
        cin >>a>>b>>c;
    int largest = a;

    if(b> largest){
        largest = b;
    }
    if(c> largest){
        largest = c;
    }
        cout <<((a + b + c == 2 * largest)? "YES\n":"NO\n");
    }


    return 0;
}