#include<bits/stdc++.h>
using namespace std;
const int MAXN=305;
int n,s;
struct Edge{int to,w;};
vector<Edge>adj[MAXN];
int maxDist,farNode;
void dfs1(int u,int fa,int dist){
    if(dist>maxDist){maxDist=dist;farNode=u;}
    for(auto&e:adj[u]){int v=e.to,w=e.w;if(v!=fa)dfs1(v,u,dist+w);}
}
int parent[MAXN],pweight[MAXN];
void dfs2(int u,int fa){
    for(auto&e:adj[u]){int v=e.to,w=e.w;if(v!=fa){parent[v]=u;pweight[v]=w;dfs2(v,u);}}
}
bool onDiameter[MAXN];
int maxDepth;
void dfs3(int u,int fa,int depth){
    if(depth>maxDepth)maxDepth=depth;
    for(auto&e:adj[u]){int v=e.to,w=e.w;if(v!=fa&&!onDiameter[v])dfs3(v,u,depth+w);}
}
int main(){
    cin>>n>>s;
    for(int i=1;i<n;i++){int u,v,w;cin>>u>>v>>w;adj[u].push_back({v,w});adj[v].push_back({u,w});}
    maxDist=-1;dfs1(1,0,0);int A=farNode;
    maxDist=-1;dfs1(A,0,0);int B=farNode;
    parent[A]=0;dfs2(A,0);
    vector<int>dia;
    for(int cur=B;cur!=0;cur=parent[cur])dia.push_back(cur);
    reverse(dia.begin(),dia.end());
    int m=dia.size();
    vector<int>preDist(m,0);
    for(int i=1;i<m;i++)preDist[i]=preDist[i-1]+pweight[dia[i]];
    memset(onDiameter,0,sizeof(onDiameter));
    for(int x:dia)onDiameter[x]=true;
    vector<int>d(m,0);
    for(int i=0;i<m;i++){maxDepth=0;dfs3(dia[i],0,0);d[i]=maxDepth;}
    int ans=1e9,j=0;
    for(int i=0;i<m;i++){
        while(j+1<m&&preDist[j+1]-preDist[i]<=s)j++;
        int leftDist=preDist[i],rightDist=preDist[m-1]-preDist[j];
        int maxD=0;
        for(int k=i;k<=j;k++)maxD=max(maxD,d[k]);
        ans=min(ans,max({leftDist,rightDist,maxD}));
    }
    cout<<ans<<endl;
    return 0;
}
/*问题：有无根树，在直径上选一条路径<=s，求树上的点到路径的最大值，
,并定义为偏心距，这个最大值的最小值是多少*/
/*思路：利用的是两次DFS求直径，因为要记录父子节点
其次，铺垫准备包括距离，标记直线节点，分支深度，然后关键公式
{leftDist,rightDist,maxD}*/
