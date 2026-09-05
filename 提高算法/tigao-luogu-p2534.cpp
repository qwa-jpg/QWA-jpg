#include<bits/stdc++.h>
using namespace std;
int n,a[25];
int h(){
    int cnt=0;
    for(int i=1;i<=n;i++)if(abs(a[i]-a[i+1])!=1)cnt++;
    return cnt;
}
bool dfs(int dep,int limit,int last){
    int g=h();
    if(g==0)return true;
    if(dep+g>limit)return false;
    if(dep==limit)return false;
    vector<pair<int,int>>cand;
    cand.reserve(n-1);
    for(int k=2;k<=n;k++){
        if(k==last)continue;
        reverse(a+1,a+1+k);
        int ng=h();
        cand.push_back({ng,k});
        reverse(a+1,a+1+k);
    }
    sort(cand.begin(),cand.end());
    for(auto[ng,k]:cand){
        reverse(a+1,a+1+k);
        if(dfs(dep+1,limit,k))return true;
        reverse(a+1,a+1+k);
    }
    return false;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    vector<int>r(n+1),tmp;
    for(int i=1;i<=n;i++){
        cin>>r[i];
        tmp.push_back(r[i]);
    }
    sort(tmp.begin(),tmp.end());
    for(int i=1;i<=n;i++)a[i]=lower_bound(tmp.begin(),tmp.end(),r[i])-tmp.begin()+1;
    a[0]=0;
    a[n+1]=n+1;
    for(int limit=(h()+1)/2;;limit++){
        if(dfs(0,limit,0)){
            cout<<limit<<'\n';
            break;
        }
    }
    return 0;
}
