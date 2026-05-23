#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
//just non-prime concept 4 and 9 both composites
    if(n % 2 == 0)
        cout << 4 <<" "<<n - 4;
    else
        cout << 9 <<" "<<n - 9;

        return 0;
}