#include<bits/stdc++.h>
using namespace std;
//num should be at 3 3
//if r>3 so move r - 3 else 3 - r
//if c>3 && c<3 than again same
int main() {
   int n,r,c;

    for(int i = 1;i <= 5;i++){
        for(int j = 1;j<= 5;j++){

            cin>>n;
            if(n==1){
                r=i;
                c=j;
            }
        }
    }
int rM = (r>3)? r - 3 : 3 - r;
int cM = (c>3)? c - 3 : 3 - c;

cout << rM + cM;
return 0;
}