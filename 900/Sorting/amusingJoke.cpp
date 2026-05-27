#include<bits/stdc++.h>
using namespace std;

int main(){

    string a,b,c;

    cin>>a>>b>>c;

    string s = a + b;

    sort(s.begin(), s.end());
    sort(c.begin(), c.end());
//a + b = c string then yes it contain all chars and sorted so extra element will make it diff
    if(s == c) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }

    return 0;
}