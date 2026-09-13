#include<bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin>>s;
    string s1 = "hello";
    int i = 0;
    for(char c : s){
        if(i == 5){
            break;
        }
        if(c== s1[i]){
            i++;
        }
    }

    cout <<(i == 5?"YES":"NO");
    return 0;
}