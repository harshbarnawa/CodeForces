#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,ct = 0;
    cin >> n;

    string str;

    for (int i = 0;i < n;i++){
        cin>> str;

        if (str[1] == '+'){
            ct++;
        } else {
        ct--;
        }
    }

    cout <<ct;

    
    return 0;
}
