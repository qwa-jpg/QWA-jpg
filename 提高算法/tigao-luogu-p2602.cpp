#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=15;
ll dp[N][N];
int num[N],now;
ll dfs(int pos,int sum,bool lead,bool limit){//lead前导0，limit最高位受限
    ll ans=0;
    if(pos==0)return sum;
    if(!lead&&!limit&&dp[pos][sum]!=-1)return dp[pos][sum];
    int up=(limit?num[pos]:9);
    for(int i=0;i<=up;i++){
        if(i==0&&lead)ans+=dfs(pos-1,sum,true,limit&&i==up);
        else if(i==now)ans+=dfs(pos-1,sum+1,false,limit&&i==up);
        else ans+=dfs(pos-1,sum,false,limit&&i==up);
    }
    if(!lead&&!limit)dp[pos][sum]=ans;
    return ans;
}
ll solve(ll x){
    int len=0;
    while(x){
        num[++len]=x%10;
        x/=10;
    }
    memset(dp,-1,sizeof(dp));
    return dfs(len,0,true,true);
}
int main(){
    ll a,b;cin>>a>>b;
    for(int i=0;i<10;i++)now=i,cout<<solve(b)-solve(a-1)<<" ";
    return 0;
}
//问题：区间内统计各个数字出现的次数
//思路：核心dfs,实现各个位置填充每个dp[][],这里利用的是ans，最后一位sum
//如果有，直接用dp,其他都是限制条件
//注意事项：limit为最高位限制，最高位选择了最大时，其他位置也要受限
