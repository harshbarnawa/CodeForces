#include<iostream>
#include<string>
#include<set>
using namespace std;

int main() {
    string s;
    getline(cin,s);

    set<char> st; //removes duplicate
    for(char c : s){
        if(c >= 'a' && c <= 'z'){ //comma , brackets skipp
            st.insert(c);
        }
    }
    
    cout << st.size();
}