#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1005,M=100005;
struct edge{int to,w;};
vector<edge>G[N],G2[N];
struct node{
    int id,dis;
    node(int a,int b){id=a;dis=b;}
    bool operator<(const node&u)const{return dis>u.dis;}
};
int dist[N];
bool done[N];
void dijkstra(int s){
    for(int i=0;i<N;i++){dist[i]=INF;done[i]=false;}
    dist[s]=0;
    priority_queue<node>q;
    q.push(node(s,dist[s]));
    while(!q.empty()){
        node u=q.top();q.pop();
        if(done[u.id])continue;
        done[u.id]=true;
        for(int i=0;i<G2[u.id].size();i++){
            edge y=G2[u.id][i];
            if(done[y.to])continue;
            if(dist[y.to]>u.dis+y.w){
                dist[y.to]=u.dis+y.w;
                q.push(node(y.to,dist[y.to]));
            }
        }
    }
}
struct point{
    int v,g,h;
    point(int a,int b,int c){v=a;g=b;h=c;}
    bool operator<(const point&b)const{return g+h>b.g+b.h;}
};
int times[N];
int astar(int s,int t,int k){
    memset(times,0,sizeof(times));
    priority_queue<point>q;
    q.push(point(s,0,0));
    while(!q.empty()){
        point p=q.top();q.pop();
        times[p.v]++;
        if(times[p.v]==k&&p.v==t)return p.g+p.h;
        for(int i=0;i<G[p.v].size();i++){
            edge y=G[p.v][i];
            q.push(point(y.to,p.g+y.w,dist[y.to]));
        }
    }
    return -1;
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    while(m--){
        int a,b,w;
        scanf("%d%d%d",&a,&b,&w);
        G[a].push_back({b,w});
        G2[b].push_back({a,w});
    }
    int s,t,k;
    scanf("%d%d%d",&s,&t,&k);
    if(s==t)k++;
    dijkstra(t);
    printf("%d\\n",astar(s,t,k));
    return 0;
}
