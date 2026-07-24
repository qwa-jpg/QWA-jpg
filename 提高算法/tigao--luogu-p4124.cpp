#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[15][11][11][2][2][2];
int num[15];
ll dfs(int pos,int u,int v,bool state,bool n8,bool n4,bool limit){
    ll ans=0;
    if(n8&&n4)return 0;
    if(!pos)return state;
    if(!limit&&dp[pos][u][v][state][n8][n4]!=-1)return dp[pos][u][v][state][n8][n4];
    int up=(limit?num[pos]:9);
    for(int i=0;i<=up;i++)
        ans+=dfs(pos-1,i,u,state||(i==u&&i==v),n8||(i==8),n4||(i==4),limit&&(i==up));
    if(!limit)dp[pos][u][v][state][n8][n4]=ans;
    return ans;
}
ll solve(ll x){
    int len=0;
    while(x){num[++len]=x%10;x/=10;}
    if(len!=11)return 0;
    memset(&dp,-1,sizeof(dp));
    ll ans=0;
    for(int i=1;i<=num[len];i++)
        ans+=dfs(len-1,i,0,0,i==8,i==4,i==num[len]);
    return ans;
}
int main(){
    ll a,b;cin>>a>>b;
    cout<<solve(b)-solve(a-1);
}
