/*给定两个正整数 a 和 b，求在 [a,b] 中的所有整数中，每个数码（digit）各出现了多少次。

输入格式
仅包含一行两个整数 a,b，含义如上所述。

输出格式
包含一行十个整数，分别表示 0～9 在 [a,b] 中出现了多少次。

输入输出样例
输入 #1复制

1 99
输出 #1复制

9 20 20 20 20 20 20 20 20 20
说明/提示
数据规模与约定
对于 30% 的数据，保证 1≤a≤b≤10 
6
 ；
对于 100% 的数据，保证 1≤a≤b≤10 
12
 。*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=15;
ll dp[N][N];
int num[N],now;
ll dfs(int pos,int sum,bool lead,bool limit){
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
