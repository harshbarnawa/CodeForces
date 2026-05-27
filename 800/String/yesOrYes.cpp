#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    string s;
    while(t--){
        cin>>s;
        for(char &c : s){ //string to lowercase
            c = tolower(c);
        }
        cout << (s=="yes"?"YES\n":"NO\n");
    }

    return 0;
}