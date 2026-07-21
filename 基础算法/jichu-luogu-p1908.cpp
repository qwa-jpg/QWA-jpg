#include<bits/stdc++.h>
const int N=5e5+5;
int a[N],tmp[N];
long long ans=0;
void Merge(int L,int mid,int R){
    int i=L,j=mid+1,t=L;
    while(i<=mid&&j<=R){
        if(a[i]>a[j]){
            ans+=mid-i+1;
            tmp[t++]=a[j++];
        }
        else tmp[t++]=a[i++];
    }
    while(i<=mid)tmp[t++]=a[i++];
    while(j<=R)tmp[t++]=a[j++];
    for(i=L;i<=R;i++)a[i]=tmp[i];
}
void Mergesort(int L,int R){
    if(L>=R)return;
    int mid=L+(R-L)/2;
    Mergesort(L,mid);
    Mergesort(mid+1,R);
    Merge(L,mid,R);
}
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    Mergesort(1,n);
    printf("%ld\n",ans);
    return 0;
}
