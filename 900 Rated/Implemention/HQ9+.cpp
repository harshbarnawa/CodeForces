#include <bits/stdc++.h>
using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    string s;
    cin >> s;
    cout << (s.find('H') != string::npos || s.find('Q') != string::npos || s.find('9') != string::npos ? "YES" : "NO");


    return 0;
}