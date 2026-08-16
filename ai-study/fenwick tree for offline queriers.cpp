/*
 * HH 的项链（洛谷 P1972 / SDOI2009）
 *
 * 题意：长度 n 的贝壳序列，m 次询问区间 [l,r] 内有多少种不同的贝壳。
 *       1 <= n, m, a_i <= 1e6。
 *
 * 思路：离线 + 树状数组。
 *   1. 把所有询问按右端点 r 从小到大排序。
 *   2. 从左到右扫描项链，维护规则：
 *      "每个种类只在其【最后一次出现的位置】贡献 1"。
 *      扫描到位置 j 时：若 a[j] 之前出现过（设位置为 p），
 *      则把 p 处的贡献 -1，再在 j 处 +1（更新 pos[a[j]] = j）。
 *   3. 对询问 [l,r]：扫描到 r 时，答案 = 前缀和(r) - 前缀和(l-1)。
 *
 * 正确性：某贝壳种类在 [l,r] 中出现 >=1 次
 *         <=> 它在 r 之前的最后一次出现位置在 [l,r] 内；
 *         若最后出现位置 < l，说明区间内根本没出现。
 *         每种最多只在最后出现处被计 1，所以不多算、不漏算。
 *
 * 复杂度：O((n + m) log n)，约 6e7 次树状数组操作，1e6 数据可过。
 *         数据量约 20MB，使用 fread 快速读入 + 缓存快速输出。
 *
 * 输入格式：第一行 n；第二行 n 个数；第三行 m；接下来 m 行 l r。
 * 输出格式：m 行，每行一个答案。
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
int n, m;
int a[MAXN];
int bit[MAXN];              // 树状数组
int pos[MAXN];              // 每种贝壳最后一次出现的位置（种类 <= 1e6）
int ans[MAXN];

struct Query {
    int l, r, id;
} q[MAXN];

// ---------- 树状数组 ----------
void add(int i, int x) {
    for (; i <= n; i += i & (-i)) bit[i] += x;
}
int sum(int i) {
    int s = 0;
    for (; i > 0; i -= i & (-i)) s += bit[i];
    return s;
}

// ---------- 快速读入（fread 缓冲） ----------
static char buf[1 << 22];
static int bidx = 0, blen = 0;
inline char get() {
    if (bidx == blen) {
        blen = (int)fread(buf, 1, sizeof(buf), stdin);
        bidx = 0;
        if (blen == 0) return EOF;
    }
    return buf[bidx++];
}
inline int read() {
    int x = 0;
    char c = get();
    while (c < '0' || c > '9') c = get();
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = get(); }
    return x;
}

// ---------- 快速输出（fwrite 缓冲） ----------
static char obuf[1 << 22];
static int oidx = 0;
inline void writeInt(int x) {
    if (x == 0) {
        obuf[oidx++] = '0';
    } else {
        char tmp[12];
        int t = 0;
        while (x) { tmp[t++] = '0' + x % 10; x /= 10; }
        while (t) obuf[oidx++] = tmp[--t];
    }
    obuf[oidx++] = '\n';
    if (oidx > (1 << 21)) { fwrite(obuf, 1, oidx, stdout); oidx = 0; }
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    m = read();
    for (int i = 0; i < m; i++) {
        q[i].l = read();
        q[i].r = read();
        q[i].id = i;
    }

    // 按右端点排序，离线扫描
    sort(q, q + m, [](const Query& x, const Query& y) {
        return x.r < y.r;
    });

    int j = 1;   // 已扫描到的位置
    for (int i = 0; i < m; i++) {
        while (j <= q[i].r) {
            if (pos[a[j]]) add(pos[a[j]], -1);  // 旧位置取消贡献
            pos[a[j]] = j;
            add(j, 1);                          // 新位置贡献 1
            j++;
        }
        ans[q[i].id] = sum(q[i].r) - sum(q[i].l - 1);
    }

    for (int i = 0; i < m; i++) writeInt(ans[i]);
    if (oidx > 0) fwrite(obuf, 1, oidx, stdout);
    return 0;
}
