#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n;
        cin>>n;

        int x = n;
        int a = 0, b = 0;

        for(int i = 2; i * i <= x;i++){
            if(x % i == 0){
                b++;
                while(x % i == 0){
                    a++;
                    x/=i;
                }
            }
        }

        if(x > 1){
            a++;
            b++;
        }
        cout << a + b-1 << '\n';

    }
}