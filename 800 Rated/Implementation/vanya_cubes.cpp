#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    int height = 0;
    int level = 1;
    int cubes = 0;

    while(cubes + level * (level + 1) / 2 <= n){
        cubes += level * (level + 1) / 2;
        height++;
        level++;
    }

    cout << height << '\n';

    return 0;
}