#include<bits/stdc++.h>
using namespace std;
const int N=6005;
int val[N],dp[N][2],father[N];
vector<int>G[N];
void addedge(int from,int to){G[from].push_back(to);father[to]=from;}
void dfs(int u){
    dp[u][0]=0;
    dp[u][1]=val[u];
    for(int v:G[u]){
        dfs(v);
        dp[u][1]+=dp[v][0];
        dp[u][0]+=max(dp[v][0],dp[v][1]);
    }
}
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&val[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);addedge(v,u);}
    int t=1;
    while(father[t])t=father[t];
    dfs(t);
    printf("%d\n",max(dp[t][0],dp[t][1]));
    return 0;
}
