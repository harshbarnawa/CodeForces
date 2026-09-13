#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    string a, b, s;
    int x = 0, y = 0;

    cin>>a; //first goal
    x++;

    while (--n){
        cin>> s;

        if(s == a) //first team
            x++;
        else{
            b = s;
            y++;
        }
    }

    cout << (x > y ? a : b);
}