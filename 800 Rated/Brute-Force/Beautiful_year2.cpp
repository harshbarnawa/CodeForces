#include<iostream>
using namespace std;

int main(){
    int y;cin>>y;

    while(1){
        y++;
        int a=y/1000,b=(y/100)%10,c=(y/10)%10,d=y%10;

        if(a!=b&&a!=c&&a!=d&&b!=c&&b!=d&&c!=d){
            cout<<y;
            break;
        }
    }
}