#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,count = 0;
    string s;
    cin>>n;
    cin>>s;

        //if neighboors are different then keep it
        //comparing just adjacent chars
        //if same remove it When removing count++
            for(int i = 0;i < n - 1;i++){
                if(s[i]==s[i+1]){
                    count++;
                }
            }
        
        cout << count;
    return 0;
}