#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;
    set<int> st;

    int p,q, level;
    cin>>p;
//making union of both set elements
    for(int i = 0;i < p;i++) {
        cin >> level;
        st.insert(level);
    }

    cin>>q;

    for(int i = 0;i < q; i++) {
        cin >> level;
        st.insert(level);
    }

    if(st.size() == n)
        cout << "I become the guy.";
    else
        cout << "Oh, my keyboard!";

        return 0;
}
