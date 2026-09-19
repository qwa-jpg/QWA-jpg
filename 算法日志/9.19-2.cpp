// ============================================================
// POJ 1270 Following Orders
// 输出 DAG 的所有拓扑序（按字典序）—— DFS 回溯 + 拓扑排序
// ============================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int n;                  // 变量个数
int deg[26];            // 入度
bool exist[26];         // 字母是否出现在变量表里
bool used[26];          // DFS 中是否已选
bool edge[26][26];      // 边 u -> v
char path[30];

void dfs(int k) {
    if (k == n) {                       // 找到一条完整拓扑序
        path[k] = 0;
        printf("%s\n", path);
        return;
    }
    for (int i = 0; i < 26; i++) {
        if (exist[i] && !used[i] && deg[i] == 0) {
            used[i] = true;
            path[k] = 'a' + i;
            for (int j = 0; j < 26; j++)
                if (edge[i][j]) deg[j]--;   // 删边
            dfs(k + 1);
            for (int j = 0; j < 26; j++)
                if (edge[i][j]) deg[j]++;   // 回溯恢复
            used[i] = false;
        }
    }
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;         // 跳过用例之间的空行

        n = 0;
        memset(exist, 0, sizeof(exist));
        memset(edge, 0, sizeof(edge));
        memset(deg, 0, sizeof(deg));
        memset(used, 0, sizeof(used));

        stringstream ss(line);
        char c;
        while (ss >> c) {
            if (!exist[c - 'a']) {          // 防重复
                exist[c - 'a'] = true;
                n++;
            }
        }

        getline(cin, line);                 // 约束行，可能为空
        stringstream cs(line);
        char u, v;
        while (cs >> u >> v) {
            if (!edge[u - 'a'][v - 'a']) {  // 防重边
                edge[u - 'a'][v - 'a'] = true;
                deg[v - 'a']++;
            }
        }

        dfs(0);
        printf("\n");                       // 每个用例后输出空行
    }
    return 0;
}

/* ============================================================
   要点说明
   ============================================================

   思路：
   ------------------------------------------------------------
   约束 x y 表示 x < y，建成有向边 x -> y。问题变成输出 DAG
   的所有拓扑排序。DFS 每层按 'a'..'z' 顺序选一个入度为 0
   且未用的字母，选中后把出边终点入度减 1，递归，回溯恢复。
   因为每层从小到大尝试，输出天然按字典序。

   读入细节：
   ------------------------------------------------------------
   第一行变量、第二行约束，用例之间有空行；约束行可能为空。
   用 getline 读整行 + stringstream 解析，空行直接 continue。

   复杂度：
   ------------------------------------------------------------
   最坏 O(n! * n)，本题数据很小，DFS 剪枝足够。题目保证有解。
*/
