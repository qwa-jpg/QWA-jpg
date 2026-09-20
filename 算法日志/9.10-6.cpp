/*某大学有 n 个职员，编号为 1…n。

他们之间有从属关系，也就是说他们的关系就像一棵以校长为根的树，父结点就是子结点的直接上司。

现在有个周年庆宴会，宴会每邀请来一个职员都会增加一定的快乐指数 r 
i
?
 ，但是呢，如果某个职员的直接上司来参加舞会了，那么这个职员就无论如何也不肯来参加舞会了。

所以，请你编程计算，邀请哪些职员可以使快乐指数最大，求最大的快乐指数。*/
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
