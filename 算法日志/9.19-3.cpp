// =====================================================================
// 洛谷 P1341 无序字母对
// 题意：n 个无序字母对，构造 n+1 个字母的字符串使每对恰好相邻出现一次
// 思路：欧拉路径
//   · 字母 = 点（52 个：'A'-'Z' -> 0..25，'a'-'z' -> 26..51）
//   · 字母对 = 无向边，字符串 = 一条经过每条边恰好一次的路径
//   1. 存在性：有边的点全部连通，且奇度点个数为 0（欧拉回路）或 2（欧拉路径）
//   2. 起点：奇度点为 2 -> 取较小的奇度点；为 0 -> 取最小的有边点
//   3. Hierholzer：邻接点按 ASCII 从小到大走边，递归删边；
//      出栈时压入栈，最后栈倒序输出即为字典序最小的路径
//   4. 走完后若还有边没删掉 => 图不连通 => No Solution
// n <= C(52,2) = 1326，递归深度 <= 1327，安全
// =====================================================================
#include <bits/stdc++.h>
using namespace std;

int g[52][52];       // 邻接矩阵存边数（题目保证字母对互不相同，但 while 兼容重边）
int deg[52];
stack<int> st;

int id(char c) { return isupper(c) ? c - 'A' : c - 'a' + 26; }

char ch(int x) { return x < 26 ? (char)('A' + x) : (char)('a' + x - 26); }

// Hierholzer：走到无路可走时把点压栈
void dfs(int u) {
    for (int v = 0; v < 52; v++) {
        while (g[u][v]) {          // 无向边两边都要删
            g[u][v]--;
            g[v][u]--;
            dfs(v);
        }
    }
    st.push(u);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char s[3];
        scanf("%s", s);
        int a = id(s[0]), b = id(s[1]);
        g[a][b]++;
        g[b][a]++;
        deg[a]++;
        deg[b]++;
    }

    int start = -1, odd = 0;
    for (int i = 0; i < 52; i++) {
        if (deg[i] & 1) {
            odd++;
            if (start == -1) start = i;   // 记录最小奇度点
        }
    }
    if (odd != 0 && odd != 2) {          // 奇度点个数不对
        puts("No Solution");
        return 0;
    }
    if (odd == 0) {                      // 欧拉回路：从最小有边点出发
        for (int i = 0; i < 52; i++)
            if (deg[i]) { start = i; break; }
    }

    dfs(start);

    // 还有边没走完 => 有边的点不连通
    for (int i = 0; i < 52; i++)
        for (int j = 0; j < 52; j++)
            if (g[i][j]) {
                puts("No Solution");
                return 0;
            }

    while (!st.empty()) {                // 栈倒序 = 字典序最小路径
        putchar(ch(st.top()));
        st.pop();
    }
    putchar('\n');
    return 0;
}
