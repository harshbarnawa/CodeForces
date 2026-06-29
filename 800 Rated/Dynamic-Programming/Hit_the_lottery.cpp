#include<bits/stdc++.h>
using namespace std;

int main() {
        ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, ct = 0;
    cin>> n;
   vector<int> vec = {100,20,10,5,1};
    for(int i : vec){
        ct += n / i;
        n %= i;
    }

    cout << ct;

    return 0;
}