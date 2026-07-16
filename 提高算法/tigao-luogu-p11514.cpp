#include<bits/stdc++.h>
using namespace std;
const int N=505;
int n,m,h[N][N];
bitset<500>bs[N*N];
int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;++i)for(int j=0;j<m;++j)scanf("%d",&h[i][j]);
    vector<int>order(n*m);
    iota(order.begin(),order.end(),0);
    sort(order.begin(),order.end(),[](int a,int b){return h[a/m][a%m]<h[b/m][b%m];});
    for(int j=0;j<m;++j){int idx=(n-1)*m+j;bs[idx].set(j);}
    for(int id:order){
        int x=id/m,y=id%m;
        for(int d=0;d<4;++d){
            int nx=x+dx[d],ny=y+dy[d];
            if(nx<0||nx>=n||ny<0||ny>=m)continue;
            if(h[nx][ny]>h[x][y]){int nid=nx*m+ny;bs[nid]|=bs[id];}
        }
    }
    bool covered[500]={false};
    for(int j=0;j<m;++j){int idx=j;for(int k=0;k<m;++k)if(bs[idx].test(k))covered[k]=true;}
    int uncov=0;
    for(int j=0;j<m;++j)if(!covered[j])++uncov;
    if(uncov){printf("0\n%d\n",uncov);return 0;}
    vector<pair<int,int>>segs;
    for(int j=0;j<m;++j){
        int idx=j,l=0,r=m-1;
        while(l<m&&!bs[idx].test(l))++l;
        while(r>=0&&!bs[idx].test(r))--r;
        if(l<=r)segs.push_back({l,r});
    }
    sort(segs.begin(),segs.end());
    int pos=0,cnt=0,i=0;
    while(pos<m){
        int maxr=-1;
        while(i<(int)segs.size()&&segs[i].first<=pos){maxr=max(maxr,segs[i].second);++i;}
        pos=maxr+1;++cnt;
    }
    printf("1\n%d\n",cnt);
    return 0;
}
