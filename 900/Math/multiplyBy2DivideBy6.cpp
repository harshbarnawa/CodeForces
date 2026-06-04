#include <bits/stdc++.h>
using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){

        long long n;
        cin >> n;

        int ct = 0;

        while(n > 1){

            if(n % 6 == 0){
                n /= 6;
                ct++;
            }
            else if(n % 3 == 0){
                n *= 2;
                ct++;
            }
            else{
                ct = -1;
                break;
            }
        }

        cout << ct << '\n';
    }

    return 0;
}