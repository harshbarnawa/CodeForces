#include<bits/stdc++.h>
using namespace std;

int main() {
    int x1,x2,x3;
    cin>>x1>>x2>>x3;

    vector<int> vec = {x1, x2, x3};
    sort(vec.begin(), vec.end());
    //(x2-x1) + (x3-x2) return sum of all interval or we can do just x3 - x1
    cout << (vec[1] - vec[0]) + (vec[2] - vec[1]);

    return 0;
}