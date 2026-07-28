#include<bits/stdc++.h>
#define ll long long
using namespace std;
char ch1;
template<class T>
inline void rd(T& x){
    x=0;bool w=0;
    ch1=getchar();
    while(!isdigit(ch1)){ch1=='-'&&(w=1),ch1=getchar();}
    while(isdigit(ch1)){x=(x<<1)+(x<<3)+(ch1&15),ch1=getchar();}
    w&&(x=(~x)+1);
}
template<class T>
inline void wr(T x){
    if(x<0)x=-x,putchar('-');
    if(x<10){putchar(x+48);return;}
    T L=x/10;
    wr(L);
    putchar(x-((L<<1)+(L<<3))+48);
}
int n,a[20],b[20],maxstep;
bool d;
int evaluate(){
    int cnt=0;
    for(int i=1;i<=n;i++)if(abs(a[i]-a[i+1])!=1)cnt++;
    return cnt;
}
void dfs(int x,int eva,int step){
    if(step==maxstep){
        if(!eva)d=1;
        return;
    }
    int temp;
    for(int i=2;i<=n;i++){
        if(i==x||abs(a[i+1]-a[i])==1)continue;
        temp=eva;
        reverse(a+1,a+i+1);
        if(abs(a[i]-a[i+1])==1)temp=eva-1;
        if(temp+step<=maxstep){
            dfs(i,temp,step+1);if(d)return;
        }
        reverse(a+1,a+i+1);
    }
}
int main(){
    rd(n);
    for(int i=1;i<=n;i++){rd(a[i]);b[i]=a[i];}
    a[n+1]=n+1;
    sort(b+1,b+n+1);
    for(int i=1;i<=n;++i)a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    for(maxstep=0;;maxstep++){
        dfs(1,evaluate(),0);
        if(d){cout<<maxstep;return 0;}
    }
}
