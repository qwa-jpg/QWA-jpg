/*给定初始串 A、目标串 B，最多6条变换规则：A_i - B_i。
规则含义：字符串中子串A_i可以替换成B_i。
求从A变成B最少需要多少次变换。
限制：最多允许10步。
 
- 若10步以内（含10）可以得到B，输出最小步数；

- 否则输出 ?NO ANSWER!?。
 
说明：本题是搜索题，不保证多项式复杂度；原题数据较水，仅作算法练习参考。
 
输入格式
 
第一行：两个字符串 A,B。
后续每行：两个字符串 A_i,B_i，代表一条替换规则，直到输入结束。
 
输出格式
 
输出最少变换步数；超过10步输出 ?NO ANSWER!
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;
const int N = 6;
int n;
string a[N], b[N];
int extend(queue <string>&q, unordered_map <string, int>&da, unordered_map <string, int>&db, string a[], string b[]){
     string t = q.front();
  q.pop();
   for (int i = 0; i < t.size(); i ++) 
      for (int j = 0; j < n; j ++)
    if (t.substr(i, a[j].size()) == a[j]){
     string state = t.substr(0, i) +b[j] + t.substr(i + a[j].size());
     if(db.count(state))   return da[t] + 1 + db[state];
     if(da.count(state))   continue;
     da[state] = da[t] + 1;
     q.push(state);
    } 
  return 11;
}
int bfs(string A,string B){
 queue <string> qa,qb;
 unordered_map <string, int> da,db;
 qa.push(A),      da[A] = 0;
 qb.push(B),      db[B] = 0;
  while(qa.size() && qb.size()){
  int t;
  if (qa.size() < qb.size())    t = extend(qa, da, db, a, b);
  else    t = extend(qb, db, da, b, a);
  if (t <= 10)    return  t;
 }
 return 11;
}
int main(){
 string A, B;
 cin >> A >> B;
 while (cin >> a[n] >> b[n])    n ++;
 int step = bfs(A, B);
 if (step > 10)     puts("NO ANSWER!");
 else               printf("%d\n", step);
 return 0;
}
