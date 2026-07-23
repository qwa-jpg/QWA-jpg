#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f,N=255,WW=1005;
int n,W;
struct{int w,t;double y;}cow[N];
double dp[WW];
bool check(double x){
    int i,j;
    for(i=1;i<=n;i++)cow[i].y=(double)cow[i].t-x*cow[i].w;
    for(i=1;i<=W;i++)dp[i]=-INF;
    dp[0]=0;
    for(i=1;i<=n;i++){
        for(j=W;j>=0;j--){
            if(j+cow[i].w>=W)dp[W]=max(dp[W],dp[j]+cow[i].y);
            else dp[j+cow[i].w]=max(dp[j+cow[i].w],dp[j]+cow[i].y);
        }
    }
    return dp[W]<0;
}
int main(){
    cin>>n>>W;
    for(int i=1;i<=n;i++)cin>>cow[i].w>>cow[i].t;
    double L=0,R=0;
    for(int i=1;i<=n;i++)R+=cow[i].t;
    for(int i=0;i<50;i++){
        double mid=L+(R-L)/2;
        if(check(mid))R=mid;
        else L=mid;
    }
    cout<<(int)(L*1000)<<endl;
    return 0;
}
