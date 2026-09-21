#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
static int down[MAXN][21], up[MAXN][21];   // 全局/静态区，避免爆栈
static int C[MAXN], pa[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<vector<int>> g(N + 1);
    for (int i = 1; i < N; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= N; i++) cin >> C[i];

    // 迭代 DFS 求先序 order 和父节点（N=1e5 链式递归会爆栈，用栈模拟）
    vector<int> order;
    order.reserve(N);
    vector<int> stk;
    stk.push_back(1);
    pa[1] = 0;
    while (!stk.empty()) {
        int u = stk.back(); stk.pop_back();
        order.push_back(u);
        for (int v : g[u])
            if (v != pa[u]) { pa[v] = u; stk.push_back(v); }
    }

    // 自底向上：down[u][d] = u 子树内到 u 距离恰为 d 的奶牛数
    for (int idx = N - 1; idx >= 0; idx--) {
        int u = order[idx];
        down[u][0] = C[u];
        for (int v : g[u])
            if (v != pa[u])
                for (int d = 1; d <= K; d++)
                    down[u][d] += down[v][d - 1];
    }

    // 自顶向下换根：up[u][d] = u 子树外到 u 距离恰为 d 的奶牛数
    // 整体(up[父][d-1] + down[父][d-1]) 减去 自己子树的贡献(down[v][d-2])
    for (int u : order) {
        for (int v : g[u])
            if (v != pa[u])
                for (int d = 1; d <= K; d++)
                    up[v][d] = up[u][d - 1] + down[u][d - 1]
                             - (d >= 2 ? down[v][d - 2] : 0);
    }

    for (int u = 1; u <= N; u++) {
        int ans = 0;
        for (int d = 0; d <= K; d++) ans += down[u][d] + up[u][d];
        cout << ans << '\n';
    }
    return 0;
}
