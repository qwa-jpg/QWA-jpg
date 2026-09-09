// POJ 1270 Following Orders
// 思路：DFS 回溯枚举所有拓扑序。
//   每层挑一个"入度为 0 且未访问"的点，把它后继的入度减 1，
//   递归下一层；回溯时恢复入度和访问标记。
//   变量先排序，按序尝试，天然保证输出字典序。
//   剪枝：只递归入度为 0 的点，砍掉大量非法排列。
//   成环时：环上点的入度永远 >= 1，选不到，cnt 走不到 n-1，自然无输出。
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;

int n, vars[26], indeg[26], topo[26];
bool g[26][26], used[26];

void dfs(int pos) {
    if (pos == n) {
        for (int i = 0; i < n; i++) putchar('a' + vars[topo[i]]);
        putchar('\n');
        return;
    }
    for (int i = 0; i < n; i++) {          // 按字典序尝试
        int v = vars[i];
        if (used[v] || indeg[v]) continue; // 入度为0且未访问才可选
        topo[pos] = i;
        used[v] = true;
        for (int j = 0; j < n; j++)
            if (g[v][vars[j]]) indeg[vars[j]]--;  // 删去后继的这条入边
        dfs(pos + 1);
        for (int j = 0; j < n; j++)
            if (g[v][vars[j]]) indeg[vars[j]]++;  // 回溯：恢复入度
        used[v] = false;
    }
}

int main() {
    char line[300];
    bool first = true;
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '\n') continue;     // 跳过用例间空行
        if (!first) putchar('\n');
        first = false;

        memset(g, 0, sizeof(g));
        memset(indeg, 0, sizeof(indeg));
        memset(used, 0, sizeof(used));

        n = 0;
        for (char *p = line; *p; p++)
            if (isalpha((unsigned char)*p)) vars[n++] = *p - 'a';
        sort(vars, vars + n);

        fgets(line, sizeof(line), stdin);
        int tmp[100], m = 0;
        for (char *p = line; *p; p++)
            if (isalpha((unsigned char)*p)) tmp[m++] = *p - 'a';
        for (int i = 0; i + 1 < m; i += 2) {   // 两两成对
            g[tmp[i]][tmp[i + 1]] = true;
            indeg[tmp[i + 1]]++;
        }
        dfs(0);
    }
    return 0;
}
