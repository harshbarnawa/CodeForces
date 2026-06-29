#include <bits/stdc++.h>
using namespace std;
//a to z == 26
int main() {
    int n;
    string s;
    cin>>n;
    cin>>s;
    if(n<26){
        cout <<"NO";
        return 0;
    } 
    set<char> st; //No duplicates allowed
    
    for(char c : s){ //string ke individual chars ko set me insert
        st.insert(tolower(c));
    }
    
 
    cout<< ((st.size()==26)?"YES":"NO");
    
    return 0;
}