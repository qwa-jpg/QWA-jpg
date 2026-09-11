/*windy 有 N 条木板需要被粉刷。 每条木板被分为 M 个格子。 每个格子要被刷成红色或蓝色。

windy 每次粉刷，只能选择一条木板上一段连续的格子，然后涂上一种颜色。 每个格子最多只能被粉刷一次。

如果 windy 只能粉刷 T 次，他最多能正确粉刷多少格子？

一个格子如果未被粉刷或者被粉刷错颜色，就算错误粉刷。

输入格式
第一行包含三个整数，N,M,T。

接下来有 N 行，每行一个长度为 M 的字符串，0 表示红色，1 表示蓝色。

输出格式
包含一个整数，最多能正确粉刷的格子数。

输入输出样例
输入 #1复制

3 6 3
111111
000000
001100
输出 #1复制

16
说明/提示
30% 的数据，满足 1≤N,M≤10,0≤T≤100。

100% 的数据，满足 1≤N,M≤50,0≤T≤2500。*/

#include<bits/stdc++.h>
using namespace std;
const int N=55,TMAX=2505;
int n,m,T;
char s[N];
int f[N][N][2];
int g[N];
int dp[TMAX];
int main(){
    scanf("%d%d%d",&n,&m,&T);
    for(int b=1;b<=n;++b){
        scanf("%s",s+1);
        memset(f,0,sizeof f);
        for(int j=1;j<=m;++j)
            for(int k=1;k<=m;++k){
                f[j][k][0]=max(f[j-1][k][0],f[j-1][k-1][1])+(s[j]=='0');
                f[j][k][1]=max(f[j-1][k][1],f[j-1][k-1][0])+(s[j]=='1');
            }
        for(int k=1;k<=m;++k)g[k]=max(f[m][k][0],f[m][k][1]);
        for(int t=T;t>=1;--t)
            for(int k=1;k<=t&&k<=m;++k)
                dp[t]=max(dp[t],dp[t-k]+g[k]);
    }
    printf("%d\n",dp[T]);
    return 0;
}
