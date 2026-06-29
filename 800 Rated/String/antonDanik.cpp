#include<bits/stdc++.h>
using namespace std;

int main () {
    int n, ct = 0;
    string s;
    cin >>n;
    cin >> s;

    for(char c : s){
        if(c=='A'){
            ct++;
        } else {
            ct--;
        }
    }
    if(ct > 0)
    cout << "Anton";
else if(ct < 0)
    cout << "Danik";
else
    cout << "Friendship";

    return 0;
}