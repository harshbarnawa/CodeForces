#include<iostream>
#include<string>
#include<set>
#include<cctype>

using namespace std;

int main() {
    string s;
    getline(cin, s);

    set<char> st;

    for(char c : s){
        if(isalpha(c)){
            st.insert(c);
        }
    }

    cout << st.size();
}