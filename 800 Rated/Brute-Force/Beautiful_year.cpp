#include<iostream>
using namespace std;

bool isDistinct(int y){
    int freq[10]={0};

    while(y>0){
        int d=y%10;
        if(freq[d]==1)return false;
        freq[d]=1;
        y/=10;
    }
    return true;
}

int main(){
    int y;cin>>y;

    while(true){
        y++;
        if(isDistinct(y)){
            cout<<y;
            break;
        }
    }
    return 0;
}