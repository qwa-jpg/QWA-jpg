#include<bits/stdc++.h>
using namespace std;
const int MAXN=1005;
int n,v[MAXN];
int dp[MAXN][MAXN];
int main(){
    cin>>n;
    for(int i=1;i<=n;++i)cin>>v[i];
    for(int i=1;i<=n;++i)dp[i][i]=v[i];
    for(int i=1;i<n;++i)dp[i][i+1]=max(v[i],v[i+1]);
    for(int len=3;len<=n;++len){
        for(int i=1;i+len-1<=n;++i){
            int j=i+len-1;
            int takeLeft=v[i]+min(dp[i+2][j],dp[i+1][j-1]);
            int takeRight=v[j]+min(dp[i+1][j-1],dp[i][j-2]);
            dp[i][j]=max(takeLeft,takeRight);
        }
    }
    cout<<dp[1][n]<<endl;
    return 0;
}
//问题：交替拿最前面和最后面的硬币，最大价值者赢
//思路：dp[i][j]是先手者在头和尾分别是i,j的最大价值,采用区间动态规划的思路
