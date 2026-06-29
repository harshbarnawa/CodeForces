#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    map<int, int> freq;
    vector<int> home;

    while (n--) {
        int h,a;
        cin>>h >> a;

        home.push_back(h);
        freq[a]++;
    }

    int ans = 0;

    for (auto h : home)
        ans += freq[h];

    cout << ans;
}