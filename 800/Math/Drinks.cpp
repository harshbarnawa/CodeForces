#include<bits/stdc++.h>
using namespace std;

int main() {
    int n,p;
    double res = 0;
    cin >> n;
//just like cgpa percetage...
    for(int i = 0 ;i < n;i++){
        cin>>p;
        res+=p;

    }
    cout<< (res/n);
}