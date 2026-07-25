#include<iostream>
#include<cstring>
using namespace std;
int n,m;
long long dp[2][1<<11];
int main(){
    while(cin>>n>>m){
        if(m>n)swap(n,m);
        memset(dp,0,sizeof(dp));
        int now=0,old=1;
        dp[now][0]=1;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                swap(now,old);
                memset(dp[now],0,sizeof(dp[now]));
                for(int k=0;k<(1<<m);k++){
                    if(k&(1<<(m-1))){
                        if(j>=1&&(k&(1<<(m-2))))continue;
                        dp[now][(k<<1)|1]+=dp[old][k];
                    }else if(k&(1<<(m-2))){
                        if(j!=0)continue;
                        if(j==0&&(k&1))continue;
                        dp[now][((k<<1)|3)&(~(1<<m))]+=dp[old][k];
                    }else{
                        dp[now][k<<1]+=dp[old][k];
                        if(j==0||(k&1)==0){
                            dp[now][(k<<1)|1]+=dp[old][k];
                        }
                    }
                }
            }
        }
        cout<<dp[now][(1<<m)-1]<<endl;
    }
    return 0;
}
