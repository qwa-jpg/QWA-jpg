#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000005;
int n,q,a[MAXN],addtag[1005],block,num,belong[MAXN],L[1005],R[1005];
vector<int>b[1005];
void rebuild(int id){
    b[id].clear();
    for(int i=L[id];i<=R[id];++i)b[id].push_back(a[i]);
    sort(b[id].begin(),b[id].end());
}
void init(){
    block=sqrt(n);
    num=(n+block-1)/block;
    for(int i=1;i<=num;++i){
        L[i]=(i-1)*block+1;
        R[i]=min(i*block,n);
    }
    for(int i=1;i<=n;++i)belong[i]=(i-1)/block+1;
    for(int i=1;i<=num;++i)rebuild(i);
}
void update(int l,int r,int w){
    int bl=belong[l],br=belong[r];
    if(bl==br){
        for(int i=l;i<=r;++i)a[i]+=w;
        rebuild(bl);
    }else{
        for(int i=l;i<=R[bl];++i)a[i]+=w;
        rebuild(bl);
        for(int i=bl+1;i<=br-1;++i)addtag[i]+=w;
        for(int i=L[br];i<=r;++i)a[i]+=w;
        rebuild(br);
    }
}
int query(int l,int r,int c){
    int bl=belong[l],br=belong[r],ans=0;
    if(bl==br){
        for(int i=l;i<=r;++i)if(a[i]+addtag[bl]>=c)++ans;
    }else{
        for(int i=l;i<=R[bl];++i)if(a[i]+addtag[bl]>=c)++ans;
        for(int i=bl+1;i<=br-1;++i){
            int target=c-addtag[i];
            auto it=lower_bound(b[i].begin(),b[i].end(),target);
            ans+=b[i].end()-it;
        }
        for(int i=L[br];i<=r;++i)if(a[i]+addtag[br]>=c)++ans;
    }
    return ans;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    init();
    char op[5];
    int l,r,w,c;
    while(q--){
        scanf("%s",op);
        if(op[0]=='M'){
            scanf("%d%d%d",&l,&r,&w);
            update(l,r,w);
        }else{
            scanf("%d%d%d",&l,&r,&c);
            printf("%d\n",query(l,r,c));
        }
    }
    return 0;
}
