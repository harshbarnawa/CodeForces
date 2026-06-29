#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> card(n);

    for(int i = 0;i < n;i++){
        cin>>card[i];
    }
    int l = 0, r = n - 1;
    int s = 0, d = 0;

    for(int i = 0; i < n; i++){
        int take;
        if(card[l] > card[r]) {
            take = card[l];
            l++;
        } else{
            take = card[r];
            r--;
        }

        if(i % 2 == 0){
            s += take;
        } else{
            d += take;
        }
    }
    cout << s << ' '<<d;
}