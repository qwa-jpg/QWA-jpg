/*5x5方块，走马均匀分配，斜对角分别是黑白两马，有一个空格*/
#include <bits/stdc++.h>
using namespace std;

const string goal = "111110111100*110000100000";
const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

// 估价函数：与目标不同的骑士格数（排除空位格）
// 一步至多修正一个骑士格，故 h 是剩余步数的下界
int h(const string &s) {
    int cnt = 0;
    for (int i = 0; i < 25; ++i)
        if (s[i] != '*' && s[i] != goal[i]) ++cnt;
    return cnt;
}

bool dfs(string &s, int pos, int dep, int limit, int last) {
    int hv = h(s);
    if (hv == 0) return true;              // 已到达目标
    if (dep + hv > limit) return false;    // 下界剪枝
    int x = pos / 5, y = pos % 5;
    for (int d = 0; d < 8; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;
        int np = nx * 5 + ny;
        if (np == last) continue;          // 不立即撤销上一步
        swap(s[pos], s[np]);
        if (dfs(s, np, dep + 1, limit, pos)) return true;
        swap(s[pos], s[np]);
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        string s;
        for (int i = 0; i < 5; ++i) {
            string row;
            cin >> row;
            s += row;
        }
        int pos = s.find('*');
        int ans = -1;
        for (int limit = 0; limit <= 15; ++limit)
            if (dfs(s, pos, 0, limit, -1)) { ans = limit; break; }
        cout << ans << '\n';
    }
    return 0;
}
