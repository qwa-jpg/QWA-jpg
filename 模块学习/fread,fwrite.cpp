// =====================================================================
// 通用快读快写模板 —— 任何题目直接复制这段到代码顶部
//   · fread 一次读 1MB 进缓冲区，逐字节解析，比 scanf/cin 快数倍
//   · 支持负数、int / long long
//   · 用法：
//       int x = read();
//       long long y = readll();
//       write(x);             // 自带换行
//       程序结束前必须加: fwrite(obuf, 1, o - obuf, stdout);  ← 千万别忘
// =====================================================================
#include <bits/stdc++.h>
using namespace std;

// ---------- 快读 ----------
char buf[1 << 20], *p1 = buf, *p2 = buf;
inline char gc() {
    return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)
               ? EOF : *p1++;
}
inline int read() {
    int x = 0, f = 1; char c = gc();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = gc(); }
    while (c >= '0' && c <= '9') x = x * 10 + (c ^ 48), c = gc();
    return x * f;
}
inline long long readll() {
    long long x = 0; int f = 1; char c = gc();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = gc(); }
    while (c >= '0' && c <= '9') x = x * 10 + (c ^ 48), c = gc();
    return x * f;
}

// ---------- 快写 ----------
char obuf[1 << 20], *o = obuf;
inline void write(int x) {
    if (x < 0) *o++ = '-', x = -x;
    static char st[15]; int top = 0;
    do st[top++] = x % 10 + '0'; while (x /= 10);
    while (top) *o++ = st[--top];
    *o++ = '\n';
}
inline void writell(long long x) {
    if (x < 0) *o++ = '-', x = -x;
    static char st[25]; int top = 0;
    do st[top++] = x % 10 + '0'; while (x /= 10);
    while (top) *o++ = st[--top];
    *o++ = '\n';
}
fwrite(obuf, 1, o - obuf, stdout);
// =====================================================================
// 洛谷 P1972 [SDOI2009] HH的项链
// 思路：离线 + 树状数组
//   1. 询问按右端点 r 从小到大排序
//   2. 从左到右扫描原数组，维护"每个值最靠右的出现位置"：
//      · 若值 a[j] 之前出现过（位置 pre[a[j]]），先在树状数组把该位置 -1
//      · 记录新位置 pre[a[j]] = j，在树状数组位置 j +1
//   3. 这样任意时刻，[1, x] 的树状数组和 = 前缀中不同数的个数
//      询问 [l, r] 答案 = sum(r) - sum(l-1)
// 复杂度 O((n+m) log n)，n, m <= 1e6，必须快读快写
// =====================================================================

const int N = 1e6 + 5;
int a[N], pre[N], c[N], ans[N];

inline void add(int x, int v) {
    for (; x < N; x += x & -x) c[x] += v;
}
inline int sum(int x) {
    int s = 0;
    for (; x; x -= x & -x) s += c[x];
    return s;
}

struct Q { int l, r, id; } q[N];

int main() {
    int n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    int m = read();
    for (int i = 1; i <= m; i++) {
        q[i].l = read(); q[i].r = read(); q[i].id = i;
    }

    // 按右端点从小到大排序
    sort(q + 1, q + m + 1, [](const Q &x, const Q &y) { return x.r < y.r; });

    int j = 1;  // 当前已扫描到的位置
    for (int i = 1; i <= m; i++) {
        // 把 [1, q[i].r] 中还没处理的位置加入树状数组
        while (j <= q[i].r) {
            if (pre[a[j]]) add(pre[a[j]], -1);  // 删除这个值上一次出现的位置
            pre[a[j]] = j;                       // 记录最新位置
            add(j, 1);                           // 在新位置 +1
            j++;
        }
        // 区间内不同数个数 = [1, r] 的和 - [1, l-1] 的和
        ans[q[i].id] = sum(q[i].r) - sum(q[i].l - 1);
    }

    for (int i = 1; i <= m; i++) write(ans[i]);
    fwrite(obuf, 1, o - obuf, stdout);  // 千万别忘，否则无输出
    return 0;
}
