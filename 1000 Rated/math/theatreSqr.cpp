#include <bits/stdc++.h>
using namespace std;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, a;
    cin>>n>>m>>a;

    long long x = n / a; //length
    long long y = m / a; //tiles width



    // these statements for if some area remains uncoverd = reminder 
    if(n % a) {
        x++; // extra tiles
    }

    if(m % a) {
        y++;
    }

    cout<< x * y;

    return 0;
}