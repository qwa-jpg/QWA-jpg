#include<bits/stdc++.h>
using namespace std;
int a[9][9],ans=-1;
int sco[9][9]={
6,6,6,6,6,6,6,6,6,
6,7,7,7,7,7,7,7,6,
6,7,8,8,8,8,8,7,6,
6,7,8,9,9,9,8,7,6,
6,7,8,9,10,9,8,7,6,
6,7,8,9,9,9,8,7,6,
6,7,8,8,8,8,8,7,6,
6,7,7,7,7,7,7,7,6,
6,6,6,6,6,6,6,6,6};
int row[9],col[9],blk[9];
int bitcnt[1<<9],lg[1<<9];
int getblk(int x,int y){return x/3*3+y/3;}
void dfs(int cnt,int cur){
    if(cnt==81){
        ans=max(ans,cur);
        return;
    }
    int x=-1,y=-1,mn=10;
    for(int i=0;i<9;++i)for(int j=0;j<9;++j)if(!a[i][j]){
        int mask=row[i]&col[j]&blk[getblk(i,j)];
        if(!mask)return;
        if(bitcnt[mask]<mn)mn=bitcnt[mask],x=i,y=j;
    }
    int mask=row[x]&col[y]&blk[getblk(x,y)];
    for(;mask;mask-=mask&-mask){
        int v=lg[mask&-mask];
        a[x][y]=v+1;
        row[x]^=1<<v;col[y]^=1<<v;blk[getblk(x,y)]^=1<<v;
        dfs(cnt+1,cur+sco[x][y]*(v+1));
        row[x]^=1<<v;col[y]^=1<<v;blk[getblk(x,y)]^=1<<v;
        a[x][y]=0;
    }
}
int main(){
    for(int i=0;i<9;++i)for(int j=0;j<9;++j)scanf("%d",&a[i][j]);
    for(int i=0;i<9;++i)row[i]=col[i]=blk[i]=(1<<9)-1;
    for(int i=0;i<(1<<9);++i)bitcnt[i]=bitcnt[i>>1]+(i&1);
    for(int i=0;i<9;++i)lg[1<<i]=i;
    int ini=0,cnt=0;
    for(int i=0;i<9;++i)for(int j=0;j<9;++j)if(a[i][j]){
        int v=a[i][j]-1;
        if(!(row[i]>>v&1)||!(col[j]>>v&1)||!(blk[getblk(i,j)]>>v&1)){printf("-1");return 0;}
        row[i]^=1<<v;col[j]^=1<<v;blk[getblk(i,j)]^=1<<v;
        ini+=sco[i][j]*a[i][j];
        ++cnt;
    }
    dfs(cnt,ini);
    printf("%d\\\\n",ans);
    return 0;
}
