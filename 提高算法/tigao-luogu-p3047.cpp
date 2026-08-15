#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=100005,MAXK=21;
int n,K,C[MAXN],fa[MAXN],dfn[MAXN];
ll down[MAXN][MAXK],tot[MAXN][MAXK];
vector<int> G[MAXN];
int main() {
    scanf("%d%d",&n,&K);
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        G[u].push_back(v),G[v].push_back(u);
    }
    for(int i=1;i<=n;i++) scanf("%d",&C[i]);
    int cnt=0;
    fa[1]=-1;
    vector<int> st={1};
    while(!st.empty()){
        int u=st.back(); st.pop_back();
        dfn[++cnt]=u;
        for(int v:G[u]) if(v!=fa[u]) fa[v]=u,st.push_back(v);
    }
    for(int i=n;i>=1;i--){
        int u=dfn[i];
        down[u][0]=C[u];
        for(int v:G[u]) if(fa[v]==u)
            for(int d=1;d<=K;d++)
                down[u][d]+=down[v][d-1];
    }
    memcpy(tot[1],down[1],sizeof(tot[1]));
    for(int i=1;i<=n;i++){
        int u=dfn[i];
        for(int v:G[u]) if(fa[v]==u){
            tot[v][0]=C[v];
            for(int d=1;d<=K;d++)
                tot[v][d]=down[v][d]+tot[u][d-1]-(d>=2?down[v][d-2]:0);
        }
    }
    for(int i=1;i<=n;i++){
        ll ans=0;
        for(int d=0;d<=K;d++) ans+=tot[i][d];
        printf("%lld\\n",ans);
    }
    return 0;
}
