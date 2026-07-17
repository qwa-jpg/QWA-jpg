#include<bits/stdc++.h>
using namespace std;
struct S{int x[4],y[4];};
char vis[8][8][8][8][8][8][8][8];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
void sortS(S&s){
    pair<int,int>p[4];
    for(int i=0;i<4;++i)p[i]={s.x[i],s.y[i]};
    sort(p,p+4);
    for(int i=0;i<4;++i)s.x[i]=p[i].first,s.y[i]=p[i].second;
}
char&V(const S&s){
    return vis[s.x[0]][s.y[0]][s.x[1]][s.y[1]]
             [s.x[2]][s.y[2]][s.x[3]][s.y[3]];
}
bool eq(const S&a,const S&b){
    for(int i=0;i<4;++i)if(a.x[i]!=b.x[i]||a.y[i]!=b.y[i])return 0;
    return 1;
}
int main(){
    S st,ed;
    for(int i=0;i<4;++i)cin>>st.x[i]>>st.y[i];
    for(int i=0;i<4;++i)cin>>ed.x[i]>>ed.y[i];
    sortS(st);sortS(ed);
    if(eq(st,ed)){cout<<"YES";return 0;}
    memset(vis,0,sizeof vis);
    queue<pair<S,int>>qf,qb;
    qf.push({st,0});V(st)=1;
    qb.push({ed,0});V(ed)=2;
    auto expand=[&](queue<pair<S,int>>&q,int dir)->bool{
        if(q.empty()||q.front().second==4)return 0;
        auto[cur,step]=q.front();q.pop();
        bool occ[8][8]={};
        for(int i=0;i<4;++i)occ[cur.x[i]][cur.y[i]]=1;
        for(int i=0;i<4;++i){
            int cx=cur.x[i],cy=cur.y[i];
            for(int d=0;d<4;++d){
                int nx=cx+dx[d],ny=cy+dy[d];
                if(nx<0||nx>7||ny<0||ny>7)continue;
                if(!occ[nx][ny]){
                    S nxt=cur;nxt.x[i]=nx;nxt.y[i]=ny;
                    sortS(nxt);
                    char&v=V(nxt);
                    if(v==0)v=dir,q.push({nxt,step+1});
                    else if(v!=dir)return 1;
                }else{
                    int nnx=nx+dx[d],nny=ny+dy[d];
                    if(nnx<0||nnx>7||nny<0||nny>7)continue;
                    if(!occ[nnx][nny]){
                        S nxt=cur;nxt.x[i]=nnx;nxt.y[i]=nny;
                        sortS(nxt);
                        char&v=V(nxt);
                        if(v==0)v=dir,q.push({nxt,step+1});
                        else if(v!=dir)return 1;
                    }
                }
            }
        }
        return 0;
    };
    while(!qf.empty()&&!qb.empty()){
        if(expand(qf,1)){cout<<"YES";return 0;}
        if(expand(qb,2)){cout<<"YES";return 0;}
        if((!qf.empty()&&qf.front().second>=4)&&(!qb.empty()&&qb.front().second>=4))break;
    }
    cout<<"NO";
    return 0;
}
