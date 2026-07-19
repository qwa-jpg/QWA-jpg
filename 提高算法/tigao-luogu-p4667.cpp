#include<bits/stdc++.h>
using namespace std;
const int dir[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
const int ab[4]={2,1,1,2};
const int cd[4][2]={{-1,-1},{-1,0},{0,-1},{0,0}};
int graph[505][505],dist[505][505];
struct P{int x,y,d;}u;
int read_ch(){
    char c;
    while((c=getchar())!='/'&&c!='\\');
    return c=='/'?1:2;
}
int main(){
    int n,m;cin>>n>>m;
    memset(dist,0x3f,sizeof(dist));
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)graph[i][j]=read_ch();
    deque<P>dq;
    dq.push_back({1,1,0});dist[1][1]=0;
    while(!dq.empty()){
        u=dq.front();dq.pop_front();
        for(int i=0;i<=3;++i){
            int nx=u.x+dir[i][0],ny=u.y+dir[i][1];
            int w=(graph[u.x+cd[i][0]][u.y+cd[i][1]]==ab[i])?0:1;
            if(nx>=1&&ny>=1&&nx<n+2&&ny<m+2&&dist[nx][ny]>dist[u.x][u.y]+w){
                dist[nx][ny]=dist[u.x][u.y]+w;
                if(w==0)dq.push_front({nx,ny,dist[nx][ny]});
                else dq.push_back({nx,ny,dist[nx][ny]});
                if(nx==n+1&&ny==m+1)break;
            }
        }
    }
    if(dist[n+1][m+1]!=0x3f3f3f3f)cout<<dist[n+1][m+1];
    else cout<<"NO SOLUTION";
    return 0;
}
