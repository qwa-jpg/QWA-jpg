#include<bits/stdc++.h>
using namespace std;
const int MAXN=70;
int n,a[MAXN],sum,max_len;
bool used[MAXN];
bool cmp(int x,int y){
	return x>y;
}
bool dfs(int cur_len,int cnt,int idx,int target,int num,int remain){
    if(cnt==num) return true;
    if(cur_len==target)
      return dfs(0,cnt+1,0,target,num,remain);
    int fail=-1;
    for(int i=idx;i<n;++i){
		if(used[i])continue;
		if(cur_len+a[i]>target) continue;
		if(a[i]==fail)continue;
		used[i]=true;
		if(dfs(cur_len+a[i],cnt,i+1,target,num,remain-a[i]))
		  return true;
		  used[i]=false;
		  fail=a[i];
		  if(cur_len==0) return false;
		  if(cur_len+a[i]==target) return false;
    }return false;}
int main(){
	scanf("%d",&n);
	int sum=0,max_len=0;
	for(int i=0;i<n;++i){
		scanf("%d",&a[i]);
		sum+=a[i];
		if(a[i]>max_len) max_len=a[i];
	}
	sort(a,a+n,cmp);
	for(int len=max_len;len<=sum;++len){
		if(sum%len!=0) continue;
		int num=sum/len;
		memset(used,0,sizeof(used));
		if(dfs(0,0,0,len,num,sum)){
			printf("%d\n",len);
			return 0;}}
			printf("%d\n",sum);
			return 0;}
