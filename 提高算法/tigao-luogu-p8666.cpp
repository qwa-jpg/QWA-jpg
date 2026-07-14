#include<stdio.h>
#include<string.h>
typedef long long ll;
int A,B,C,n,m;
const int N=1000005;
ll s[N],D[N];
int x2[N],y2[N],z2[N];
int x1[N],y1[N],z1[N];
int d[N];
int num(int x,int y,int z){
    if(x>A||y>B||z>C)return 0;
    return((x-1)*B+(y-1))*C+(z-1)+1;
}
bool check(int x){
    memset(D,0,sizeof(D));
    for(int i=1;i<=x;i++){
        int idx;
        idx=num(x1[i],y1[i],z1[i]);if(idx)D[idx]+=d[i];
        idx=num(x2[i]+1,y1[i],z1[i]);if(idx)D[idx]-=d[i];
        idx=num(x1[i],y2[i]+1,z1[i]);if(idx)D[idx]-=d[i];
        idx=num(x2[i]+1,y2[i]+1,z1[i]);if(idx)D[idx]+=d[i];
        idx=num(x1[i],y1[i],z2[i]+1);if(idx)D[idx]-=d[i];
        idx=num(x2[i]+1,y1[i],z2[i]+1);if(idx)D[idx]+=d[i];
        idx=num(x1[i],y2[i]+1,z2[i]+1);if(idx)D[idx]+=d[i];
        idx=num(x2[i]+1,y2[i]+1,z2[i]+1);if(idx)D[idx]-=d[i];
    }
    for(int i=1;i<=A;i++)
        for(int j=1;j<=B;j++)
            for(int k=1;k<C;k++)
                D[num(i,j,k+1)]+=D[num(i,j,k)];
    for(int i=1;i<=A;i++)
        for(int k=1;k<=C;k++)
            for(int j=1;j<B;j++)
                D[num(i,j+1,k)]+=D[num(i,j,k)];
    for(int j=1;j<=B;j++)
        for(int k=1;k<=C;k++)
            for(int i=1;i<A;i++)
                D[num(i+1,j,k)]+=D[num(i,j,k)];
    for(int i=1;i<=n;i++)
        if(D[i]>s[i])return true;
    return false;
}
int main(){
    scanf("%d%d%d%d",&A,&B,&C,&m);
    n=A*B*C;
    for(int i=1;i<=n;i++)scanf("%lld",&s[i]);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d%d%d%d%d",&x1[i],&x2[i],&y1[i],&y2[i],&z1[i],&z2[i],&d[i]);
    int L=1,R=m;
    while(L<R){
        int mid=(L+R)>>1;
        if(check(mid))R=mid;
        else L=mid+1;
    }
    printf("%d\\n",R);
    return 0;
}
