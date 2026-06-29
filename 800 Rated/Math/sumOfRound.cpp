#include<bits/stdc++.h>
using namespace std;

int main() {
    int t,n;
    cin>>t;

    while(t--){
        int n;
        cin>>n;
        vector<int> ans;

        int place = 1;
        while(n != 0) {

            int digit = n % 10;

            if(digit != 0) { //making round num here
                ans.push_back(digit * place);
            }

            n /= 10;
            place *= 10;
        }

        cout << ans.size() << endl; //min count

        for(int x : ans) { //round numbers
            cout << x << " ";
        }

        cout << endl;
    }

    return 0;
}