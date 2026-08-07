#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=305;
void solve(){
    int T;cin>>T;
    while(T--){
        int n,m;ll M;cin>>n>>m>>M;
        int fix[MAXN]={0};
        for(int i=0;i<m;i++){int p,q;cin>>p>>q;fix[q]++;}
        int pref[MAXN]={0};
        for(int i=1;i<=n;i++)pref[i]=pref[i-1]+fix[i];
        int unfixed=n-m;
        ll C[MAXN][MAXN]={{0}};
        for(int i=0;i<=unfixed;i++){
            C[i][0]=C[i][i]=1%M;
            for(int j=1;j<i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%M;
        }
        vector<ll>dp_mod(unfixed+1,0);
        vector<bool>dp_ok(unfixed+1,false);
        dp_mod[0]=1%M;dp_ok[0]=true;
        for(int v=1;v<=n;v++){
            vector<ll>nxt_mod(unfixed+1,0);
            vector<bool>nxt_ok(unfixed+1,false);
            int need_base=v-pref[v];
            for(int s=0;s<=unfixed;s++){
                if(!dp_ok[s])continue;
                int min_t=max(0,need_base-s);
                int max_t=unfixed-s;
                for(int t=min_t;t<=max_t;t++){
                    int ns=s+t;
                    nxt_ok[ns]=true;
                    nxt_mod[ns]=(nxt_mod[ns]+dp_mod[s]*C[unfixed-s][t])%M;
                }
            }
            dp_mod=move(nxt_mod);
            dp_ok=move(nxt_ok);
        }
        if(!dp_ok[unfixed])cout<<"NO\\\\n";
        else cout<<"YES "<<dp_mod[unfixed]<<"\\\\n";
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
