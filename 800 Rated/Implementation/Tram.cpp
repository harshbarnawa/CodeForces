#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int curr = 0, ans = 0;

    while (n--)
    {
        int a, b;
        cin >> a >> b;

        curr -= a;
        curr += b;

        ans = max(ans, curr);
    }

    cout << ans << endl;

    return 0;
}