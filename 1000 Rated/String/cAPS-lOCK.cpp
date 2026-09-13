#include<bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin>>s;
    bool upp = true;
    for(int i = 1;i < s.size();i++){
        if(islower(s[i])){
            upp = false;
            break;
        }
    }
    if(upp){
        for(char  &c : s){
            if(islower(c)){
                c = toupper(c);
            }   else{
                c = tolower(c);
            }
        }
        
    }
    cout << s;
}