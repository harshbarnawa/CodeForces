#include<bits/stdc++.h>
using namespace std;

int main() {
 int n, ans = 0;
    cin >> n;
    string s;
//Making map json type so that i compare easily (key value pair)
    map<string, int> faces = {
        {"Tetrahedron", 4},
        {"Cube", 6},
        {"Octahedron", 8},
        {"Dodecahedron", 12},
        {"Icosahedron", 20}
    };
    while (n--) {
        cin >> s;
        ans += faces[s]; //adding values as per key
    }

    cout << ans;
return 0;
}