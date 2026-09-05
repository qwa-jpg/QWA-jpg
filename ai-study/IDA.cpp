#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 50;
int n, a[MAXN + 5], b[MAXN + 5];
bool sol;

inline int h() {//最完美估价 
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        cnt += abs(a[i] - a[i + 1]) != 1;
    return cnt;
}

void dfs(int g, int f, int pre) {
    if (sol || g + h() > f) return;//预估步数
    if (!h()) {
        sol = 1;//找到答案 
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (i == pre) continue;//保证不与上一次翻转的长度相同 
        reverse(a + 1, a + i + 1);//翻转 
        dfs(g + 1, f, i);
        reverse(a + 1, a + i + 1);//回溯 
    }
}

int main() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; ++i)
        a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;//离散化 
    a[n + 1] = n + 1;
    for (int i = 0; ; ++i) {//迭代加深 
        sol = 0;
        dfs(0, i, 0);
        if (sol) {
            write(i);
            putchar('\n');
            break;
        }
    }
    return 0;
}
