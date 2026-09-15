// 洛谷 P1197 [JSOI2008] 星球大战
// 思路：离线倒序 + 并查集（时光倒流）
//   正向删点并查集无法维护（只能合不能拆），但摧毁顺序全部离线给出，
//   所以把时间倒过来看：从"全部炸完"的残局开始，每次复活一个点。
//   复活 = 加点 + 连边，连通块变化只与邻居有关，并查集 O(α) 维护：
//   1. 初始只加入从未被摧毁的点，合并其间的边，cnt = 幸存点数 - 合并次数；
//   2. 倒序枚举攻击序列：先记录当前 cnt 为该次攻击后的答案，
//      再复活点 u（cnt++），并把它与所有"已复活"的邻居合并（成功一次 cnt--）；
//   3. 最后输出初始 cnt（全部复活完的状态），再正序输出记录的 k 个答案。
#include <bits/stdc++.h>
using namespace std;

const int N = 400005;               // n <= 2m <= 4e5

int fa[N];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n);       // 存完整图（摧毁顺序未知，不能边读边并）
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int k;
    cin >> k;
    vector<int> atk(k), destroyed(n, 0);
    for (int i = 0; i < k; i++) {
        cin >> atk[i];
        destroyed[atk[i]] = 1;
    }

    for (int i = 0; i < n; i++) fa[i] = i;

    // 残局：只有从未被摧毁的点，合并它们之间的边
    int cnt = n - k;
    for (int u = 0; u < n; u++) {
        if (destroyed[u]) continue;
        for (int v : g[u]) {
            if (destroyed[v]) continue;
            if (find(u) != find(v)) {
                merge(u, v);
                cnt--;
            }
        }
    }

    // 倒序复活：ans[i] = 第 i 次攻击后的连通块数
    vector<int> ans(k);
    for (int i = k - 1; i >= 0; i--) {
        ans[i] = cnt;               // 复活前 = 第 i 次攻击后的状态
        int u = atk[i];
        destroyed[u] = 0;
        cnt++;                      // 孤点成块
        for (int v : g[u]) {
            if (destroyed[v]) continue;
            if (find(u) != find(v)) {
                merge(u, v);
                cnt--;
            }
        }
    }

    cout << cnt << '\n';            // 初始状态（全部复活）
    for (int i = 0; i < k; i++)
        cout << ans[i] << '\n';

    return 0;
}
