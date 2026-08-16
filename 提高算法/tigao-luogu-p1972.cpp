#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
int n, m;
int a[MAXN];
int bit[MAXN];
int pos[MAXN];
int ans[MAXN];
struct Query {
    int l, r, id;
} q[MAXN];
void add(int i, int x) {
    for (; i <= n; i += i & (-i)) bit[i] += x;
}
int sum(int i) {
    int s = 0;
    for (; i > 0; i -= i & (-i)) s += bit[i];
    return s;
}
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
    sort(q, q + m, [](const Query& x, const Query& y) {
        return x.r < y.r;
    });
    int j = 1;
    for (int i = 0; i < m; i++) {
        while (j <= q[i].r) {
            if (pos[a[j]]) add(pos[a[j]], -1);
            pos[a[j]] = j;
            add(j, 1);
            j++;
        }
        ans[q[i].id] = sum(q[i].r) - sum(q[i].l - 1);
    }
    for (int i = 0; i < m; i++) writeInt(ans[i]);
    if (oidx > 0) fwrite(obuf, 1, oidx, stdout);
    return 0;
}
