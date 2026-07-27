#include<bits/stdc++.h>
using namespace std;
const int MAXN=100005;
const int MAXB=320;
int a[MAXN];
int n,m;
int block_size;
int block_id[MAXN];
int block[10][10][MAXB];
int pow10[10];
void init(){
    block_size=sqrt(n);
    if(block_size==0)block_size=1;
    int block_num=(n+block_size-1)/block_size;
    memset(block,0,sizeof(block));
    for(int i=1;i<=n;++i){
        block_id[i]=(i-1)/block_size;
        int val=a[i];
        for(int d=0;d<10;++d){
            int digit=(val/pow10[d])%10;
            block[d][digit][block_id[i]]++;
        }
    }
}
void update(int x,int y){
    int bid=block_id[x];
    int old_val=a[x];
    for(int d=0;d<10;++d){
        int digit=(old_val/pow10[d])%10;
        block[d][digit][bid]--;
    }
    a[x]=y;
    for(int d=0;d<10;++d){
        int digit=(y/pow10[d])%10;
        block[d][digit][bid]++;
    }
}
int query(int L,int R,int D,int P){
    int d=D-1;
    int ans=0;
    int lid=block_id[L];
    int rid=block_id[R];
    if(lid==rid){
        for(int i=L;i<=R;++i){
            if((a[i]/pow10[d])%10==P)ans++;
        }
        return ans;
    }
    for(int i=L;i<(lid+1)*block_size+1;++i){
        if((a[i]/pow10[d])%10==P)ans++;
    }
    for(int b=lid+1;b<=rid-1;++b){
        ans+=block[d][P][b];
    }
    for(int i=rid*block_size+1;i<=R;++i){
        if((a[i]/pow10[d])%10==P)ans++;
    }
    return ans;
}
int main(){
    pow10[0]=1;
    for(int i=1;i<10;++i)pow10[i]=pow10[i-1]*10;
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)scanf("%d",&a[i]);
        init();
        char op[2];
        int x,y,L,R,D,P;
        while(m--){
            scanf("%s",op);
            if(op[0]=='S'){
                scanf("%d%d",&x,&y);
                update(x,y);
            }else{
                scanf("%d%d%d%d",&L,&R,&D,&P);
                printf("%d\n",query(L,R,D,P));
            }
        }
    }
    return 0;
}
