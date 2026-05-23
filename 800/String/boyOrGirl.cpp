#include<bits/stdc++.h>
using namespace std;
//lets separate string into individual chars
//creating new s2 string copying only non duplicates
//then just even odd logic
int main() {
    string s1,s2;
    cin >> s1;
    int freq[256] = {0};
    for (char c : s1){
         if(freq[c] == 0) {
            s2 += c;
            freq[c]++;
        }
    }
    if(s2.length()%2==0){
             cout << "CHAT WITH HER!";
        } else {
             cout<< "IGNORE HIM!";
        }

        return 0;
}