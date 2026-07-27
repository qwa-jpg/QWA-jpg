#include<bits/stdc++.h>
using namespace std;
const int MAXN=200005;
int n,m,block;
int k[MAXN];
int step[MAXN],to[MAXN];
void rebuild(int id){
    int L=id*block;
    int R=min(n-1,L+block-1);
    for(int i=R;i>=L;--i){
        int nxt=i+k[i];
        if(nxt>=n||nxt/block!=id){
            step[i]=1;
            to[i]=nxt;
        }else{
            step[i]=step[nxt]+1;
            to[i]=to[nxt];
        }
    }
}
int query(int x){
    int res=0;
    while(x<n){
        res+=step[x];
        x=to[x];
    }
    return res;
}
int main(){
    scanf("%d",&n);
    block=(int)sqrt(n)+1;
    for(int i=0;i<n;++i)scanf("%d",&k[i]);
    for(int i=0;i<n;i+=block)rebuild(i/block);
    scanf("%d",&m);
    while(m--){
        int op,j;
        scanf("%d%d",&op,&j);
        if(op==1){
            printf("%d\n",query(j));
        }else{
            int newk;
            scanf("%d",&newk);
            k[j]=newk;
            rebuild(j/block);
        }
    }
    return 0;
}
