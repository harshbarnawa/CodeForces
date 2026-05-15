#include<iostream>
#include<string>
using namespace std;

int main() {
    string s1;
    int ct= 0;
    int ct2 = 0;
    cin>>s1;
    
    for(char c : s1){
        if(islower(c)){
            ct++;
        } else{
            ct2++;
        }
    }
    if(ct>=ct2){
        for(char &c : s1){
          c = tolower(c);
        }
        cout << s1;
    } else {
        
        for(char &c : s1){
          c = toupper(c);
        }
        cout << s1;
    }
    return 0;
}