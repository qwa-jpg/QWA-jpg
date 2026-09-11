/*有一头奶牛冲出了围栏，来到了一处圣地（对于奶牛来说），上面用牛语写着一段文字。
现用汉语翻译为：
有 N 个区间，每个区间 x,y 表示提供的 x～y 共 y?x+1 堆优质牧草。你可以选择任意区间但不能有重复的部分。
对于奶牛来说，自然是吃的越多越好，然而奶牛智商有限，现在请你帮助他。
输入格式
第一行一个整数 N。
接下来 N 行，每行两个数 x,y，描述一个区间。
输出格式
输出最多能吃到的牧草堆数。*/
#include<bits/stdc++.h>
using namespace std;
const int N=150005;
struct Seg{int l,r;}a[N];
int rs[N],bit[N],m;
void upd(int p,int v){
    for(;p<=m;p+=p&-p)bit[p]=max(bit[p],v);
}
int qry(int p){
    int res=0;
    for(;p>0;p-=p&-p)res=max(res,bit[p]);
    return res;
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d%d",&a[i].l,&a[i].r);
        rs[i]=a[i].r;
    }
    sort(rs+1,rs+n+1);
    m=unique(rs+1,rs+n+1)-rs-1;
    sort(a+1,a+n+1,[](Seg&x,Seg&y){return x.l<y.l;});
    int ans=0;
    for(int i=1;i<=n;++i){
        int p=lower_bound(rs+1,rs+m+1,a[i].l)-rs-1;
        p=min(p,m);
        int dp=a[i].r-a[i].l+1+qry(p);
        ans=max(ans,dp);
        int q=lower_bound(rs+1,rs+m+1,a[i].r)-rs;
        upd(q,dp);
    }
    printf("%d\n",ans);
    return 0;
}
