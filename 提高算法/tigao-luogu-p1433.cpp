#include<bits/stdc++.h>
using namespace std;
int n;
double x[20],y[20];
double dist[20][20];
double memo[1<<16][20];
bool vis[1<<16][20];
double dfs(int mask,int last){
	if(mask==(1<<n)-1) return 0.0;
	if(vis[mask][last]) return memo[mask][last];
	double ans=1e18;
	for(int i=1;i<=n;++i){
		if(!(mask&(1<<(i-1)))){
			ans=min(ans,dist[last][i]+dfs(mask|(1<<(i-1)),i));
		}
	}
	vis[mask][last]=true; 
	return memo[mask][last]=ans;
		}
int main(){
	scanf("%d",&n);
	x[0]=y[0]=0;
	for(int i=1;i<=n;++i){
		scanf("%lf%lf",&x[i],&y[i]);
	}
	for(int i=0;i<=n;++i){
		for(int j=0;j<=n;++j){
			double dx=x[i]-x[j];
			double dy=y[i]-y[j];
			dist[i][j]=sqrt(dx*dx+dy*dy);
		}
	}
	double ans=dfs(0,0);
	printf("%.2f\n",ans);
	return 0;
}
