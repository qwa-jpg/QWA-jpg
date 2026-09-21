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
#include <bits/stdc++.h>
using namespace std;

string A, B;
vector<string> from, to;

// 单侧 BFS：从 start 出发做 src->dst 的替换
// me: 本侧距离表, other: 对侧距离表(可能为空), 返回遇到的最短总步数
int bfsOne(const string& start, const vector<string>& src,
           const vector<string>& dst,
           unordered_map<string, int>& me, unordered_map<string, int>& other) {
    queue<string> q;
    me[start] = 0;
    q.push(start);
    int best = 11;                        // >10 视为无解
    while (!q.empty()) {
        string s = q.front(); q.pop();
        int d = me[s];
        if (d == 5) continue;             // 每侧最多 5 层，两侧合计 <= 10
        for (int i = 0; i < (int)src.size(); i++) {
            for (size_t pos = 0; (pos = s.find(src[i], pos)) != string::npos; pos++) {
                string t = s.substr(0, pos) + dst[i] + s.substr(pos + src[i].size());
                if (me.count(t)) continue;
                if (other.count(t)) {     // 与对侧相遇 -> 记录总步数
                    best = min(best, d + 1 + other[t]);
                } else {
                    me[t] = d + 1;
                    q.push(t);
                }
            }
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> A >> B;
    string x, y;
    while (cin >> x >> y) { from.push_back(x); to.push_back(y); }

    if (A == B) { cout << 0 << '\n'; return 0; }

    unordered_map<string, int> d1, d2;
    bfsOne(A, from, to, d1, d2);              // 正向：填 d1（此时 d2 空，无相遇）
    int ans = bfsOne(B, to, from, d2, d1);    // 反向：填 d2 并检测相遇

    if (ans <= 10) cout << ans << '\n';
    else cout << "NO ANSWER!" << '\n';
    return 0;
}
