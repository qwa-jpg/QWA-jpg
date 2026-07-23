#include<bits/stdc++.h>
using namespace std;
int main(){
    string a,b;cin>>a>>b;
    int n=a.size(),m=b.size();
    vector<int>dp(m+1),ndp(m+1);
    for(int j=0;j<=m;++j)dp[j]=j;
    for(int i=1;i<=n;++i){
        ndp[0]=i;
        for(int j=1;j<=m;++j){
            if(a[i-1]==b[j-1])ndp[j]=dp[j-1];
            else ndp[j]=min(dp[j],min(ndp[j-1],dp[j-1]))+1;
        }
        swap(dp,ndp);
    }
    cout<<dp[m]<<'\n';
    return 0;
}
