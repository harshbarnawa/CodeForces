#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        int n;
        string a,b;

        cin >> n >> a >> b;

        vector<int> ae,ao,be,bo;

        for(int i=0;i<n;i++){
            if(a[i]=='1'){
                if(i%2==0) ae.push_back(i);
                else ao.push_back(i);
            }

            if(b[i]=='1'){
                if(i%2==0) be.push_back(i);
                else bo.push_back(i);
            }
        }

        if(ae.size()!=be.size() || ao.size()!=bo.size()){
            cout << -1 << '\n';
            continue;
        }

        long long ans=0;

        for(int i=0;i<(int)ae.size();i++){
            ans+=abs(ae[i]-be[i])/2;
        }

        for(int i=0;i<(int)ao.size();i++){
            ans+=abs(ao[i]-bo[i])/2;
        }

        cout << ans << '\n';
    }
}