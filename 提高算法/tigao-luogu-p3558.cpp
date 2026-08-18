#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
int main(){
    int n,a;
    scanf("%d",&n);
    int dp[3]={INF,INF,INF};
    scanf("%d",&a);
    dp[a+1]=0;
    for(int i=2;i<=n;i++){
        scanf("%d",&a);
        int ndp[3]={INF,INF,INF};
        for(int j=0;j<3;j++){
            for(int k=0;k<=j;k++){
                int cost;
                if(k==0){
                    if(a>=j-1)cost=a-(j-1);
                    else cost=INF;
                }else if(k==1){
                    if(a==j-1)cost=0;
                    else cost=INF;
                }else{
                    if(a<=j-1)cost=(j-1)-a;
                    else cost=INF;
                }
                if(dp[k]<INF&&cost<INF)
                    ndp[j]=min(ndp[j],dp[k]+cost);
            }
        }
        memcpy(dp,ndp,sizeof(dp));
    }
    int ans=min(dp[0],min(dp[1],dp[2]));
    printf(ans>=INF?"BRAK\\n":"%d\\n",ans);
    return 0;
}
