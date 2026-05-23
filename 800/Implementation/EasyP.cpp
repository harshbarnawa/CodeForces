#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
bool b = false;
    vector<int> a(n);

for(int i = 0; i < n; i++){
    cin >> a[i];
    if(a[i] == 1){
        b = true;
    }
}
    
    cout << (b?"HARD":"EASY");
}