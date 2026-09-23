// =====================================================================
// 树状数组（BIT）经典例题合集 —— 按题型循序渐进
// 用法：修改下方 SOLVE 为题号，编译运行对应题目
//   SOLVE=1  洛谷 P3374  单点修改 + 区间求和
//   SOLVE=2  洛谷 P3368  区间修改 + 单点查询（差分 BIT）
//   SOLVE=3  洛谷 P3372  区间修改 + 区间求和（双 BIT）
//   SOLVE=4  洛谷 P1908  逆序对（离散化 + 权值 BIT）
//   SOLVE=5  洛谷 P1972  HH 的项链（离线 BIT 求区间不同数）
//   SOLVE=6  POJ 2182    Lost Cows（BIT 上二分求第 k 小）
//   SOLVE=7  POJ 2352    Stars（二维偏序）
//   SOLVE=8  洛谷 P1020  导弹拦截（BIT 优化 LIS）
//   SOLVE=9  POJ 1195    Mobile phones（二维 BIT）
//   SOLVE=10 CSP 201709-5 除法（BIT + set 均摊，真题）
// =====================================================================
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;

#define SOLVE 1

// =====================================================================
#if SOLVE == 1
// ============ 1. 洛谷 P3374 【模板】树状数组 1 ============
// 题目内容：已知一个数列 a[1..n]，进行 m 次操作：
//   1 x k  -> 将第 x 个数加上 k
//   2 x y  -> 输出区间 [x,y] 内每个数的和
// 数据范围：n, m <= 5e5
// 思路：树状数组最基础用法。
//   add：单点修改，沿 lowbit 向上爬，O(log n)
//   sum：求前缀和 [1..i]，沿 lowbit 向下跳，O(log n)
//   区间和 [x,y] = sum(y) - sum(x-1)
//   累加值用 long long 防溢出
const int MAXN = 500000 + 5;
int n, m;
ll bit[MAXN];
void add(int i, ll x) { for (; i <= n; i += i & -i) bit[i] += x; }
ll sum(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) { int x; scanf("%d", &x); add(i, x); }
    while (m--) {
        int op, x, y; scanf("%d%d%d", &op, &x, &y);
        if (op == 1) add(x, y);
        else printf("%lld\n", sum(y) - sum(x - 1));
    }
    return 0;
}
// =====================================================================
#elif SOLVE == 2
// ============ 2. 洛谷 P3368 【模板】树状数组 2 ============
// 题目内容：已知一个数列 a[1..n]，进行 m 次操作：
//   1 x y k -> 区间 [x,y] 每个数加上 k
//   2 x     -> 输出第 x 个数的值
// 数据范围：n, m <= 5e5
// 思路：差分数组 + 树状数组（区间修改、单点查询）
//   设差分 d[i] = a[i] - a[i-1]，则 a[x] = d[1]+...+d[x]
//   区间加 [x,y] k 等价于 d[x] += k, d[y+1] -= k（两个单点修改）
//   BIT 维护差分数组，查询即前缀和
const int MAXN = 500000 + 5;
int n, m;
ll bit[MAXN];
void add(int i, ll x) { for (; i <= n; i += i & -i) bit[i] += x; }
ll sum(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    scanf("%d%d", &n, &m);
    int last = 0;
    for (int i = 1; i <= n; i++) { int x; scanf("%d", &x); add(i, x - last); last = x; }
    while (m--) {
        int op; scanf("%d", &op);
        if (op == 1) {
            int x, y, k; scanf("%d%d%d", &x, &y, &k);
            add(x, k); add(y + 1, -k);
        } else {
            int x; scanf("%d", &x);
            printf("%lld\n", sum(x));
        }
    }
    return 0;
}
// =====================================================================
#elif SOLVE == 3
// ============ 3. 洛谷 P3372 【模板】线段树 1（双树状数组写法） ============
// 题目内容：已知数列 a[1..n]，进行 m 次操作：
//   1 x y k -> 区间 [x,y] 每个数加上 k
//   2 x y   -> 输出区间 [x,y] 的和
// 数据范围：n, m <= 1e5
// 思路：两个 BIT 维护差分数组，实现"区间修改 + 区间求和"
//   设差分 d[i]，前缀和 S(x) = Σ_{i=1..x} a[i]
//       = Σ_{i=1..x} d[i] * (x - i + 1)
//       = (x+1) * Σd[i] - Σ i*d[i]
//   用 bit1 维护 Σd[i]，bit2 维护 Σ i*d[i]
//   区间加 [x,y] k：
//       bit1[x] += k, bit1[y+1] -= k
//       bit2[x] += k*x, bit2[y+1] -= k*(y+1)
//   区间和 [x,y] = S(y) - S(x-1)
const int MAXN = 100000 + 5;
int n, m;
ll bit1[MAXN], bit2[MAXN];
void add(ll *b, int i, ll x) { for (; i <= n; i += i & -i) b[i] += x; }
ll sum(ll *b, int i) { ll s = 0; for (; i > 0; i -= i & -i) s += b[i]; return s; }
void range_add(int l, int r, ll k) {
    add(bit1, l, k);      add(bit1, r + 1, -k);
    add(bit2, l, k * l);  add(bit2, r + 1, -k * (r + 1));
}
ll prefix(int x) { return (ll)(x + 1) * sum(bit1, x) - sum(bit2, x); }
int main() {
    scanf("%d%d", &n, &m);
    int last = 0;
    for (int i = 1; i <= n; i++) { int x; scanf("%d", &x); range_add(i, i, x - last); last = x; }
    while (m--) {
        int op, x, y; scanf("%d%d%d", &op, &x, &y);
        if (op == 1) { ll k; scanf("%lld", &k); range_add(x, y, k); }
        else printf("%lld\n", prefix(y) - prefix(x - 1));
    }
    return 0;
}
// =====================================================================
#elif SOLVE == 4
// ============ 4. 洛谷 P1908 逆序对 ============
// 题目内容：给定序列 a[1..n]，求逆序对个数，即满足 i < j 且 a[i] > a[j] 的
//   (i, j) 对数。
// 数据范围：n <= 5e5，|a[i]| <= 1e9
// 思路：离散化 + 权值树状数组
//   值域 1e9 太大，先离散化压缩到 1..m（只保留大小关系）
//   BIT 记录"当前已出现过的值"各出现几次（以离散化排名为下标）
//   从左到右扫描，扫到第 i 个（前面已插入 i 个）：
//     比 a[i] 大的个数 = 已插入总数 - 小于等于 a[i] 的个数
//     即 ans += i - sum(rk)，然后 add(rk, 1)
//   答案最大 C(n,2) 约 1.25e11，用 long long
const int MAXN = 500000 + 5;
int n, a[MAXN], b[MAXN];
ll bit[MAXN];
void add(int i, int x) { for (; i <= n; i += i & -i) bit[i] += x; }
ll sum(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) { scanf("%d", &a[i]); b[i] = a[i]; }
    sort(b, b + n);
    int m = unique(b, b + n) - b;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int rk = lower_bound(b, b + m, a[i]) - b + 1;  // 排名 1..m
        ans += (ll)i - sum(rk);   // 已插入 i 个，其中 <= a[i] 的有 sum(rk) 个
        add(rk, 1);
    }
    printf("%lld\n", ans);
    return 0;
}
// =====================================================================
#elif SOLVE == 5
// ============ 5. 洛谷 P1972 [SDOI2009] HH 的项链 ============
// 题目内容：长度为 n 的序列 a[1..n]，m 次询问，每次给出 [l, r]，
//   求区间内有多少个不同的数。
// 数据范围：n, m <= 1e6，a[i] <= 1e6
// 思路：离线 + 树状数组（经典"区间不同数"套路）
//   把询问按右端点 r 升序排序，从左到右扫描序列：
//   BIT 第 i 位 = 1 表示 a[i] 是其值"当前最靠右的一次出现"
//   扫到 a[i]：若该值之前出现过（last[a[i]]），把那个位置 -1；
//             再把 i 位置 +1，更新 last[a[i]] = i
//   这样任意时刻，[l, r] 的区间和 = 区间内不同值的个数
//   处理所有右端点 == i 的询问：ans = sum(r) - sum(l-1)
// 复杂度：O((n + m) log n)
const int MAXN = 1000000 + 5;
int n, m, a[MAXN], last[MAXN];
ll bit[MAXN];
struct Query { int l, r, id; } q[MAXN];
bool cmp(const Query &x, const Query &y) { return x.r < y.r; }
int ans_q[MAXN];
void add(int i, int x) { for (; i <= n; i += i & -i) bit[i] += x; }
ll sum(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &m);
    for (int i = 0; i < m; i++) { scanf("%d%d", &q[i].l, &q[i].r); q[i].id = i; }
    sort(q, q + m, cmp);
    for (int i = 1, j = 0; i <= n; i++) {
        if (last[a[i]]) add(last[a[i]], -1);  // 抹掉旧位置
        last[a[i]] = i;
        add(i, 1);                            // 标记新位置
        while (j < m && q[j].r == i) {        // 右端点已扫到的询问
            ans_q[q[j].id] = (int)(sum(q[j].r) - sum(q[j].l - 1));
            j++;
        }
    }
    for (int i = 0; i < m; i++) printf("%d\n", ans_q[i]);
    return 0;
}
// =====================================================================
#elif SOLVE == 6
// ============ 6. POJ 2182 Lost Cows ============
// 题目内容：N 头牛排成一排，编号 1..N。已知第 i 头牛前面比它编号小的牛的
//   数量 pre[i]（pre[1] = 0）。输入 N，再输入 pre[2..N] 共 N-1 个数，
//   输出每头牛的编号。
// 数据范围：N <= 8000
// 思路：倒序 + 权值 BIT 上二分
//   正着推不动（后面会插队），从最后一头往前推：
//   第 i 头牛的编号 = 当前剩余编号中第 (pre[i]+1) 小的
//   BIT 初始每个编号占 1（都可用），
//   kth(k) 在 BIT 上倍增二分找"前缀和 >= k 的最小位置"，找到后该位置置 0
// 复杂度：O(n log n)
const int MAXN = 8000 + 5;
int n, pre[MAXN], ans[MAXN], bit[MAXN];
void add(int i, int x) { for (; i <= n; i += i & -i) bit[i] += x; }
int kth(int k) {                    // 最小 x 使 sum(x) >= k（BIT 上倍增二分）
    int x = 0;
    for (int p = 1 << 13; p; p >>= 1)
        if (x + p <= n && bit[x + p] < k) { k -= bit[x + p]; x += p; }
    return x + 1;
}
int main() {
    scanf("%d", &n);
    pre[1] = 0;
    for (int i = 2; i <= n; i++) scanf("%d", &pre[i]);
    for (int i = 1; i <= n; i++) add(i, 1);
    for (int i = n; i >= 1; i--) {
        ans[i] = kth(pre[i] + 1);
        add(ans[i], -1);            // 该编号被占用
    }
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}
// =====================================================================
#elif SOLVE == 7
// ============ 7. POJ 2352 Stars ============
// 题目内容：给出 N 颗星星的坐标 (x, y)（已按 y 升序、y 相同按 x 升序给出）。
//   星星的等级 = 左下方（x' <= x 且 y' <= y）星星的个数（不含自己）。
//   输出等级为 0..N-1 的星星各有多少颗。
// 数据范围：N <= 15000，0 <= x, y <= 32000
// 思路：二维偏序计数，输入已按 y 排序，降为一维
//   处理每颗星时，之前插入的星星 y' <= y 自动满足，
//   只需统计 x' <= x 的个数 = sum(x+1)（BIT 下标从 1 开始，坐标 +1）
//   统计完等级后把该星 x 插入 BIT
const int MAXX = 32000 + 5;
int n, bit[MAXX], level[15005];
void add(int i, int x) { for (; i < MAXX; i += i & -i) bit[i] += x; }
int sum(int i) { int s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        int lv = sum(x + 1);        // 已插入的 x' <= x 的个数
        level[lv]++;
        add(x + 1, 1);
    }
    for (int i = 0; i < n; i++) printf("%d\n", level[i]);
    return 0;
}
// =====================================================================
#elif SOLVE == 8
// ============ 8. 洛谷 P1020 [NOIP1999 提高组] 导弹拦截 ============
// 题目内容：输入一串导弹高度（若干整数，个数未知，读到 EOF 结束），求：
//   第 1 问：一套系统最多能拦截多少枚（拦截序列高度不上升）
//   第 2 问：要拦截所有导弹，最少需要多少套系统
// 数据范围：导弹数 n <= 1e5
// 思路：BIT 优化 LIS，O(n log n)
//   第 1 问 = 最长不上升子序列：
//     dp[i] = max(dp[j]) + 1，j < i 且 h[j] >= h[i]
//     离散化后把值域"反转"（大高度排前面），
//     查询前缀 max 即得"高度 >= h[i]"的最大 dp
//   第 2 问 = 最长严格上升子序列长度（Dilworth 定理）：
//     查询高度 < h[i] 的前缀 max
//   BIT 维护"以某高度结尾的子序列最大长度"（前缀最大值 BIT）
const int MAXN = 100000 + 5;
int h[MAXN], b[MAXN], n = 0;
int bit[MAXN];
void upd(int i, int x) { for (; i <= n; i += i & -i) bit[i] = max(bit[i], x); }
int qry(int i) { int s = 0; for (; i > 0; i -= i & -i) s = max(s, bit[i]); return s; }
int main() {
    int x;
    while (scanf("%d", &x) != EOF) { h[n] = x; b[n] = x; n++; }
    sort(b, b + n);
    int m = unique(b, b + n) - b;

    // 第 1 问：最长不上升子序列（值域反转：大高度排前面）
    int ans1 = 0;
    memset(bit, 0, sizeof(bit));
    for (int i = 0; i < n; i++) {
        int pos = m - (int)(lower_bound(b, b + m, h[i]) - b);  // 反转后位置 1..m
        int d = qry(pos) + 1;         // 高度 >= h[i] 的最大 dp
        ans1 = max(ans1, d);
        upd(pos, d);
    }

    // 第 2 问：最长严格上升子序列
    int ans2 = 0;
    memset(bit, 0, sizeof(bit));
    for (int i = 0; i < n; i++) {
        int pos = (int)(lower_bound(b, b + m, h[i]) - b) + 1;  // 1..m
        int d = qry(pos - 1) + 1;     // 高度 < h[i]（严格小于）的最大 dp
        ans2 = max(ans2, d);
        upd(pos, d);
    }
    printf("%d\n%d\n", ans1, ans2);
    return 0;
}
// =====================================================================
#elif SOLVE == 9
// ============ 9. POJ 1195 Mobile phones ============
// 题目内容：S x S 的二维矩阵（初始全 0），支持以下指令：
//   0 S       -> 初始化矩阵大小 S（可能多次出现，重新置零）
//   1 X Y A   -> (X, Y) 加上 A（坐标 0 基）
//   2 L B R T -> 查询子矩阵和：左边界 L、下边界 B、右边界 R、上边界 T
//   3         -> 结束
// 数据范围：S <= 1024
// 思路：二维树状数组（单点修改 + 矩阵求和）
//   add/sum 双重循环，一维 BIT 的二维推广
//   矩阵和 = sum(r+1, t+1) - sum(l, t+1) - sum(r+1, b) + sum(l, b)
//   （坐标 0 基转 1 基，容斥原理）
const int MAXS = 1024 + 5;
int S;
ll bit[MAXS][MAXS];
void add(int x, int y, ll a) {
    for (int i = x; i <= S; i += i & -i)
        for (int j = y; j <= S; j += j & -j)
            bit[i][j] += a;
}
ll sum(int x, int y) {
    ll s = 0;
    for (int i = x; i > 0; i -= i & -i)
        for (int j = y; j > 0; j -= j & -j)
            s += bit[i][j];
    return s;
}
int main() {
    int op;
    while (scanf("%d", &op) && op != 3) {
        if (op == 0) {
            scanf("%d", &S);
            memset(bit, 0, sizeof(bit));
        } else if (op == 1) {
            int x, y, a; scanf("%d%d%d", &x, &y, &a);
            add(x + 1, y + 1, a);
        } else {
            int l, b, r, t; scanf("%d%d%d%d", &l, &b, &r, &t);
            ll ans = sum(r + 1, t + 1) - sum(l, t + 1) - sum(r + 1, b) + sum(l, b);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
// =====================================================================
#elif SOLVE == 10
// ============ 10. CSP 201709-5 除法（真题） ============
// 题目内容：长度为 n 的数组 a[1..n]，m 次操作：
//   1 l r v -> 对 [l, r] 中所有能被 v 整除的数 a[i]，执行 a[i] /= v
//   2 l r   -> 输出区间 [l, r] 的和
// 数据范围：n, m <= 1e5，a[i] <= 1e6
// 思路：树状数组维护区间和 + set 均摊遍历
//   BIT 只支持单点修改，所以每除一次就单点更新一次
//   用 set 存"值 > 1 的下标"，操作 1 只遍历 set 中落在 [l, r] 的位置：
//     若 v >= 2 且 a[i] % v == 0：单点更新 BIT，a[i] /= v
//     a[i] 变 1 后不会再变，从 set 删除
//   均摊分析：a[i] <= 1e6，每次除法至少减半，一个数最多除约 20 次到 1，
//   所以 set 总访问次数 O(n log maxV)，每次 O(log n)，总复杂度可过 1e5
const int MAXN = 100000 + 5;
int n, m;
ll a[MAXN], bit[MAXN];
set<int> alive;                    // 值 > 1 的下标集合
void add(int i, ll x) { for (; i <= n; i += i & -i) bit[i] += x; }
ll sum(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        add(i, a[i]);
        if (a[i] > 1) alive.insert(i);
    }
    while (m--) {
        int op, l, r; scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            int v; scanf("%d", &v);
            if (v <= 1) continue;  // 除以 1 值不变，跳过
            set<int>::iterator it = alive.lower_bound(l);
            while (it != alive.end() && *it <= r) {
                int i = *it;
                if (a[i] % v == 0) {
                    add(i, a[i] / v - a[i]);   // BIT 单点更新差值
                    a[i] /= v;
                }
                if (a[i] == 1) it = alive.erase(it);  // 变 1 后不会再变
                else ++it;
            }
        } else {
            printf("%lld\n", sum(r) - sum(l - 1));
        }
    }
    return 0;
}
// =====================================================================
#endif
