#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;//1e9
int m,n;
int g[105][105];
int dist[105][105][2];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
struct Node{
    int cost,x,y,c;
    bool operator<(const Node&o)const{return cost>o.cost;}
};
int main(){
    scanf("%d%d",&m,&n);
    memset(g,-1,sizeof(g));
    for(int i=0;i<n;i++){
        int x,y,c;
        scanf("%d%d%d",&x,&y,&c);
        g[x][y]=c;
    }
    memset(dist,0x3f,sizeof(dist));
    priority_queue<Node>q;
    dist[1][1][g[1][1]]=0;
    q.push({0,1,1,g[1][1]});
    while(!q.empty()){
        Node t=q.top();q.pop();
        if(t.cost>dist[t.x][t.y][t.c])continue;
        for(int k=0;k<4;k++){
            int nx=t.x+dx[k],ny=t.y+dy[k];
            if(nx<1||nx>m||ny<1||ny>m)continue;
            if(g[nx][ny]!=-1){
                int nc=t.cost+(t.c!=g[nx][ny]);
                if(nc<dist[nx][ny][g[nx][ny]]){
                    dist[nx][ny][g[nx][ny]]=nc;
                    q.push({nc,nx,ny,g[nx][ny]});
                }
            }else if(g[t.x][t.y]!=-1){
                int nc=t.cost+2;
                if(nc<dist[nx][ny][t.c]){
                    dist[nx][ny][t.c]=nc;
                    q.push({nc,nx,ny,t.c});
                }
            }
        }
    }
    int ans=INF;
    if(g[m][m]!=-1)ans=dist[m][m][g[m][m]];
    else ans=min(dist[m][m][0],dist[m][m][1]);
    if(ans>=INF)ans=-1;
    printf("%d\n",ans);
    return 0;
}
