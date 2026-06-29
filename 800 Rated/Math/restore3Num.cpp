#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<long long> x(4);
    for(int i = 0;i<4;i++){
        cin>>x[i];
    }
    sort(x.begin(),x.end());
int largest = x[3];
int ct= 0;
    for(int i : x){
        if(ct==3){
            break;
        }
        cout << largest - i<< " ";
        ct++;
    }

    return 0;
}