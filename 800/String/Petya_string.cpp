#include <bits/stdc++.h>
using namespace std;

int main() {
    string s1, s2;

    cin>>s1>> s2;

     for(char &c : s1) {
        c = tolower(c);
    }
    for(char &c : s2) {
        c = tolower(c);
    }

cout <<(s1 < s2 ? -1: (s1 > s2 ? 1 : 0));
    return 0;
}