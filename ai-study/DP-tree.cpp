// 洛谷 P2605 [ZJOI2010] 基站选址
// 思路：DP + 线段树优化 + 滚动数组
//   L[i]/R[i] = 能覆盖村庄 i 的最左/最右基站下标（二分）
//   dp[i][j] = 前 i 个村庄，建 j 个站，第 j 个站在 i 的最小总费用
//   转移：dp[i][j] = C[i] + min_{k=j-1}^{i-1} { dp[k][j-1] + Σ W[t] }
//        其中 t∈(k,i)，且 L[t]>k、R[t]<i（夹在中间又两边都罩不住，必须补偿）
//
// 线段树的运用：
//   固定 j，从左到右扫 i。当 i 越过 R[t]（i = R[t]+1）时，村庄 t 对右站永久失去
//   覆盖可能，此后对所有 k < L[t] 的候选左站都要多付 W[t]。
//   所以维护 val[k] = dp[k][j-1] + 已过期村庄的补偿，
//   每右移一位 i，把 R[t]=i-1 的村庄的 W[t] 区间加到 [0, L[t]-1]（前缀区间加）。
//
// 滚动数组：
//   dp 只依赖上一层，所以只用一维数组 f[] 存"当前层"；
//   每层开始时用 f（此时仍存上一层 dp[k][j-1]）重建线段树，
//   层内算出的 dp[i][j] 再写回 f[i]，供下一层使用。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 20005;
const ll INF = 1e18;

int n, K;
ll d[N], c[N], s[N], w[N];
int L[N], R[N];
vector<int> ins[N];          // ins[R[t]]：右覆盖端点等于该值的村庄（到期时统一加补偿）
ll f[N];                     // 滚动数组：f[i] = dp[i][j]（当前层）
ll tail[N];                  // tail[i] = Σ_{t>i, L[t]>i} w[t]（最后一个站右侧村庄的补偿）
ll mn[N << 2], tag[N << 2];  // 线段树：区间最小值 + 区间加懒标记

void build(int o, int l, int r) {
    tag[o] = 0;
    if (l == r) { mn[o] = f[l]; return; }
    int m = (l + r) >> 1;
    build(o << 1, l, m);
    build(o << 1 | 1, m + 1, r);
    mn[o] = min(mn[o << 1], mn[o << 1 | 1]);
}
void apply(int o, ll v) { mn[o] += v; tag[o] += v; }
void push(int o) {
    if (tag[o]) {
        apply(o << 1, tag[o]);
        apply(o << 1 | 1, tag[o]);
        tag[o] = 0;
    }
}
void add(int o, int l, int r, int ql, int qr, ll v) {
    if (ql > qr) return;
    if (ql <= l && r <= qr) { apply(o, v); return; }
    push(o);
    int m = (l + r) >> 1;
    if (ql <= m) add(o << 1, l, m, ql, qr, v);
    if (qr > m) add(o << 1 | 1, m + 1, r, ql, qr, v);
    mn[o] = min(mn[o << 1], mn[o << 1 | 1]);
}
ll query(int o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return mn[o];
    push(o);
    int m = (l + r) >> 1;
    ll res = INF;
    if (ql <= m) res = min(res, query(o << 1, l, m, ql, qr));
    if (qr > m) res = min(res, query(o << 1 | 1, m + 1, r, ql, qr));
    return res;
}

int main() {
    scanf("%d%d", &n, &K);
    d[1] = 0;
    for (int i = 2; i <= n; i++) scanf("%lld", &d[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &c[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &s[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &w[i]);

    // 二分求覆盖区间端点
    for (int i = 1; i <= n; i++) {
        L[i] = lower_bound(d + 1, d + n + 1, d[i] - s[i]) - d;
        R[i] = upper_bound(d + 1, d + n + 1, d[i] + s[i]) - d - 1;
        ins[R[i]].push_back(i);
    }

    // 尾部补偿后缀和
    tail[n] = 0;
    for (int i = n - 1; i >= 0; i--)
        tail[i] = tail[i + 1] + (L[i + 1] > i ? w[i + 1] : 0);

    // 初始化滚动数组：j = 0 层（一个站都不建，全补偿）
    for (int i = 1; i <= n; i++) f[i] = INF;
    f[0] = 0;
    ll ans = tail[0];

    // 滚动：逐层计算 j = 1..min(K, n)，只用 f[] 一维
    for (int j = 1; j <= min(K, n); j++) {
        for (int i = 0; i < j - 1; i++) f[i] = INF;  // 清理不可行的 k（j-1 个站必在 >= j-1 处）
        build(1, 0, n);                              // 用上一层 f 重建树：tree[k] = dp[k][j-1]

        for (int i = j; i <= n; i++) {
            for (int t : ins[i - 1])                 // 到期村庄：补偿加给所有 k < L[t]
                add(1, 0, n, 0, L[t] - 1, w[t]);
            f[i] = c[i] + query(1, 0, n, j - 1, i - 1);  // dp[i][j] 写回滚动数组
        }

        // 本层答案：min{ dp[i][j] + 右侧村庄补偿 }（至多 K 个站，取所有层的最小值）
        for (int i = j; i <= n; i++)
            ans = min(ans, f[i] + tail[i]);
    }

    printf("%lld\n", ans);
    return 0;
}
