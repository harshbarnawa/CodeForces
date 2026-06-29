#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        vector<string> target(10);

        for(int i = 0; i < 10; i++){
            cin >> target[i];
        }

        int ans = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++){
                if(target[i][j] == 'X'){
                    ans += min({i, j, 9 - i, 9 - j}) + 1; //min distance from any border
                }
            }
        }

        cout << ans << '\n';
    }

    return 0;
}