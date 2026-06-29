#include<bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin>>s;
     int ct = 1;

     if((s.length())<7){ //Optimization
        cout << "NO";
        return 0;
     }
    for (int i = 1;i < s.length(); i++){
        if(s[i] == s[i - 1]){
            ct++;
            if(ct >= 7){
                cout <<"YES";
                return 0;
            }
        } else{
            ct = 1;
        }
    }
    cout <<"NO";

}