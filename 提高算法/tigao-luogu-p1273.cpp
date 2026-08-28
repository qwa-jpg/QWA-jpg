#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define rep(i,a,b) for(int i=(a);i<(b);++i)
const int N=3010;
int n,m;
vector<pii>g[N];
int val[N];
int sz[N];
int dp[N][N];
int ord[N],tot;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-m;++i){
        int k;scanf("%d",&k);
        while(k--){
            int a,c;scanf("%d%d",&a,&c);
            g[i].push_back(pii(a,c));
        }
    }
    for(int i=n-m+1;i<=n;++i)scanf("%d",&val[i]);
    memset(dp,0xc0,sizeof dp);
    stack<int>st;st.push(1);
    while(!st.empty()){
        int x=st.top();st.pop();
        ord[++tot]=x;
        rep(i,0,(int)g[x].size())st.push(g[x][i].first);
    }
    for(int id=tot;id>=1;--id){
        int u=ord[id];
        dp[u][0]=0;
        if(u>n-m){
            sz[u]=1;
            dp[u][1]=val[u];
            continue;
        }
        rep(i,0,(int)g[u].size()){
            int v=g[u][i].first,w=g[u][i].second;
            for(int j=sz[u];j>=0;--j)
                for(int k=1;k<=sz[v];++k)
                    dp[u][j+k]=max(dp[u][j+k],dp[u][j]+dp[v][k]-w);
            sz[u]+=sz[v];
        }
    }
    for(int i=m;i>=0;--i)
        if(dp[1][i]>=0){printf("%d\\n",i);return 0;}
    return 0;
}
