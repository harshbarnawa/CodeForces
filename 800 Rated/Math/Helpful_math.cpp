#include<bits/stdc++.h>
using namespace std;

int main() {
    vector<char> temp;
    string s;
    cin>>s;

    for(char c : s){
        if(c!='+'){
            temp.push_back(c);
        }
    }
    sort(temp.begin(),temp.end());

    for(int i = 0;i<temp.size();i++){
        cout << temp[i];

        if(i != temp.size() - 1){
            cout << "+";
        }
    }


    return 0;
}