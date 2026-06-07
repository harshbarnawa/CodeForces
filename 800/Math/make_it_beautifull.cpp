#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;

        vector<int> a(n);
        for (int &x : a){ 
            cin >> x;
        }

        if(a[0] == a[n - 1]){ //kya nahi  hona chaiye
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";

        cout << a[n - 1] << ' ';

        for(int i = 0; i < n - 1; i++){
      if(i == n - 2){
            cout << a[i] << '\n';
        }else{
             cout << a[i] << ' ';
        }
        }
    }

    return 0;
}