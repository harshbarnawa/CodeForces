#include<iostream>
#include<vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
cin.tie(NULL);

int t;
cin>>t;

while(t--){
int n;
cin>>n;

vector<int>a(n);
for(int i=0;i<n;i++)
    cin>>a[i];

vector<int>f(n+1,0);
int ans=-1;

for(int i=0;i<n;i++){
    f[a[i]]++;

    if(f[a[i]]==3){
        ans=a[i];
        break;
    }
}

cout<<ans<<'\n';
}

return 0;
}