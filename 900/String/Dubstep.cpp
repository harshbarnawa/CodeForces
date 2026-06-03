#include<bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin>>s;
    string w;

     for(int i = 0;i < s.size();i++){
        if(i + 2 < s.size() && s[i]=='W' && s[i+1]=='U' && s[i+2]=='B' ){
            i+=2;
            
            if(!w.empty())
                w+=' ';
        }
         else {
            w+=s[i];
        }
     }
     cout << w;


    return 0;
}