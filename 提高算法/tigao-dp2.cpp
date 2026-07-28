#include<bits/stdc++.h>
using namespace std;
string s(string str1,string str2){
    int n=str1.size(),m=str2.size();
    vector<vector<int>>dp(n+1,vector<int>(m+1,0));
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j){
        if(str1[i-1]==str2[j-1])dp[i][j]=dp[i-1][j-1]+1;
        else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    }
    int i=n,j=m;
    string ans;
    while(i>0||j>0){
        if(i>0&&j>0&&str1[i-1]==str2[j-1]){
            ans.push_back(str1[i-1]);--i;--j;
        }else if(j==0||(i>0&&dp[i-1][j]>dp[i][j-1])){
            ans.push_back(str1[i-1]);--i;
        }else{
            ans.push_back(str2[j-1]);--j;
        }
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
int main(){
    string str1,str2;cin>>str1>>str2;
    cout<<s(str1,str2)<<endl;
    return 0;
}
//问题：两个字符串，str1,str2,找一个最短字符串，使它俩为子序列（不要求字符串紧邻）
//思路：利用dp构造LCS长度计算，即最短公用长度，dp[i][j]为str1的前i个字符和str2的前j个字符的LCS长度
