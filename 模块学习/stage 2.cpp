// =====================================================================
// 搜索专题合集 —— 按 CSP 400 分目标（T1-T4 全对）三层顺序编排
// 用法：修改下方 SOLVE 为题号，编译运行对应题目
//
// 第 1 层 地基（先补，T1-T4 通用）
//   SOLVE=1  洛谷 P1706  全排列（DFS 回溯框架）
//   SOLVE=2  洛谷 P1157  组合的输出（DFS 回溯：递增枚举防重）
//   SOLVE=3  洛谷 P1036  选数（DFS 回溯 + 剪枝 + 素数判定）
//   SOLVE=4  洛谷 P1443  马的遍历（BFS 最短路模板）
//   SOLVE=5  CSP 201604-4 游戏（BFS 三维状态：位置 + 时间）
//   SOLVE=6  洛谷 P1596  Lake Counting（Flood Fill 八连通染色）
//   SOLVE=7  CSP 201409-4 最优配餐（多源 BFS）
//   SOLVE=8  洛谷 P1434  滑雪（记忆化搜索）
//
// 第 2 层 T4 必备（最短路家族）
//   SOLVE=9  洛谷 P4779  单源最短路径（Dijkstra 堆优化模板）
//   SOLVE=10 CSP 201703-4 地铁修建（Dijkstra 变体：最小化最大边权）
//   SOLVE=11 洛谷 P1113  杂务（拓扑排序 Kahn + DP）
//   SOLVE=12 洛谷 P4017  最大食物链计数（拓扑排序 + 计数 DP）
//   SOLVE=13 洛谷 P3956  棋盘（0-1 BFS 双端队列）
//
// 第 3 层 冲分加强
//   SOLVE=14 洛谷 P4799  世界冰球锦标赛（折半搜索 meet in the middle）
//   SOLVE=15 洛谷 P1379  八数码难题（A* = BFS + 估价函数）
// =====================================================================
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define SOLVE 1

// =====================================================================
#if SOLVE == 1
// ============ 1. 洛谷 P1706 全排列问题 ============
// 题目内容：输出自然数 1..n 所有不重复的排列（n 的全排列），
//   要求按字典序输出，每个数字占 5 个字符宽度（%5d）。
// 数据范围：1 <= n <= 9
// 思路：DFS 回溯框架（最基础的深搜模板）
//   dfs(k) 填第 k 位：尝试每个没用过的数 i，标记、递归、回溯撤销标记
//   回溯 = 递归返回后撤销本层的选择，回到上一层换下一个数
//   按 1..n 从小到大尝试，天然字典序
int n, a[10], vis[10];
void dfs(int k) {
    if (k == n) {                       // 填满 n 位，输出
        for (int i = 0; i < n; i++) printf("%5d", a[i]);
        printf("\n");
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = 1;                 // 选 i
            a[k] = i;
            dfs(k + 1);
            vis[i] = 0;                 // 回溯：撤销
        }
    }
}
int main() {
    scanf("%d", &n);
    dfs(0);
    return 0;
}
// =====================================================================
#elif SOLVE == 2
// ============ 2. 洛谷 P1157 组合的输出 ============
// 题目内容：从自然数 1..n 中任取 r 个数的所有组合，按字典序输出，
//   每个数字占 3 个字符宽度（%3d）。
// 数据范围：1 <= r <= n <= 21
// 思路：DFS 回溯 + "递增枚举"防重
//   与全排列的区别：组合不区分顺序，{1,3} 与 {3,1} 算同一种
//   技巧：dfs(k, start) 只从 start 开始选，保证 a[k] 严格递增，
//   每种组合只会被枚举一次，天然有序
//   剪枝：剩下 n - i 个数不够填满剩余 (r - k) 位时提前返回
int n, r, a[25];
void dfs(int k, int start) {
    if (k == r) {
        for (int i = 0; i < r; i++) printf("%3d", a[i]);
        printf("\n");
        return;
    }
    for (int i = start; i <= n - (r - k) + 1; i++) {  // 剪枝：剩下不够选
        a[k] = i;
        dfs(k + 1, i + 1);
    }
}
int main() {
    scanf("%d%d", &n, &r);
    dfs(0, 1);
    return 0;
}
// =====================================================================
#elif SOLVE == 3
// ============ 3. 洛谷 P1036 [NOIP2002 普及组] 选数 ============
// 题目内容：已知 n 个整数 x1..xn，从中任选 k 个整数相加，
//   问和为素数的方案共有多少种。
// 数据范围：1 <= n <= 20，k < n，|xi| <= 5e6
// 思路：DFS 组合枚举 + 素数判定
//   与组合输出同框架，枚举所有 C(n,k) 种选法（C(20,10) 约 18 万，暴力可过）
//   递归携带 sum，选满 k 个时判断 sum 是否素数
//   素数判定：试除到 sqrt(x)
int n, k, a[25], ans;
bool isPrime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return true;
}
void dfs(int start, int cnt, int sum) {
    if (cnt == k) {                     // 选满 k 个
        if (isPrime(sum)) ans++;
        return;
    }
    for (int i = start; i <= n - (k - cnt) + 1; i++)  // 剪枝
        dfs(i + 1, cnt + 1, sum + a[i]);
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    dfs(1, 0, 0);
    printf("%d\n", ans);
    return 0;
}
// =====================================================================
#elif SOLVE == 4
// ============ 4. 洛谷 P1443 马的遍历 ============
// 题目内容：n x m 的棋盘，马在 (x, y)，按"日"字形走（8 个方向），
//   求马走到棋盘每个格子的最少步数，走不到输出 -1。
// 数据范围：1 <= n, m <= 400
// 思路：BFS 求无权图最短路（标准模板）
//   队列先进先出保证第一次到达某格就是最短步数
//   dist 数组：-1 表示没到过（兼做 visited），到过即最短
//   输出左对齐 5 位（%-5d）
const int MAXN = 405;
int n, m, sx, sy;
int dist[MAXN][MAXN];
int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int main() {
    scanf("%d%d%d%d", &n, &m, &sx, &sy);
    memset(dist, -1, sizeof(dist));
    queue<pair<int, int> > q;
    dist[sx][sy] = 0;
    q.push(make_pair(sx, sy));
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (dist[nx][ny] == -1) {           // 第一次到 = 最短路
                dist[nx][ny] = dist[x][y] + 1;
                q.push(make_pair(nx, ny));
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) printf("%-5d", dist[i][j]);
        printf("\n");
    }
    return 0;
}
// =====================================================================
#elif SOLVE == 5
// ============ 5. CSP 201604-4 游戏 ============
// 题目内容：n x m 方格，从 (1,1) 走到 (n,m)，每秒可向上下左右移动一格。
//   某些格子 (r,c) 在时间段 [a,b] 内是危险的，期间不能进入。
//   求到达 (n,m) 的最短时间（秒）。
// 数据范围：1 <= n, m <= 100，危险时间段不超过 9999 个
// 思路：BFS 三维状态（x, y, t）
//   普通 BFS 是 (x,y) 二维，本题格子能否进入随时间变化，
//   把时间也放进状态：vis[x][y][t] 表示 t 时刻是否到过 (x,y)
//   答案 t <= 300 足够（n,m <= 100 时最短时间不会超过 300，官方数据保证）
//   注意：同一格可能有多个危险时间段，用 vector 存区间
struct Node { int x, y, t; };
bool vis[105][105][305];
vector<pair<int, int> > bad[105][105];
int n, m;
bool danger(int x, int y, int t) {
    for (size_t i = 0; i < bad[x][y].size(); i++)
        if (bad[x][y][i].first <= t && t <= bad[x][y][i].second) return true;
    return false;
}
int main() {
    int k;
    scanf("%d%d%d", &n, &m, &k);
    while (k--) {
        int r, c, a, b;
        scanf("%d%d%d%d", &r, &c, &a, &b);
        bad[r][c].push_back(make_pair(a, b));
    }
    queue<Node> q;
    q.push((Node){1, 1, 0});
    vis[1][1][0] = true;
    while (!q.empty()) {
        Node f = q.front(); q.pop();
        if (f.x == n && f.y == m) { printf("%d\n", f.t); return 0; }
        if (f.t >= 300) continue;               // 数据保证答案 <= 300
        int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
        for (int d = 0; d < 4; d++) {
            int nx = f.x + dx[d], ny = f.y + dy[d];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (vis[nx][ny][f.t + 1]) continue;
            if (danger(nx, ny, f.t + 1)) continue;   // 下一时刻该格危险
            vis[nx][ny][f.t + 1] = true;
            q.push((Node){nx, ny, f.t + 1});
        }
    }
    return 0;
}
// =====================================================================
#elif SOLVE == 6
// ============ 6. 洛谷 P1596 [USACO10OCT] Lake Counting ============
// 题目内容：N x M 的园地，'W' 表示水洼，'.' 表示旱地。
//   八连通（横竖斜相邻）的水洼连成一片算一个湖，求湖的数量。
// 数据范围：1 <= N, M <= 100
// 思路：Flood Fill 洪水填充（DFS 染色）
//   遍历每个格子，遇到 'W' 就把它连通的整片 'W' 都染成 '.'（DFS 淹没），
//   每淹没一片计数 +1
//   本质：统计八连通块个数
const int MAXN = 105;
int n, m, ans;
char g[MAXN][MAXN];
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
void dfs(int x, int y) {
    g[x][y] = '.';                      // 淹没当前格
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if (g[nx][ny] == 'W') dfs(nx, ny);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%s", g[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (g[i][j] == 'W') { ans++; dfs(i, j); }
    printf("%d\n", ans);
    return 0;
}
// =====================================================================
#elif SOLVE == 7
// ============ 7. CSP 201409-4 最优配餐 ============
// 题目内容：n x n 网格城市，有 m 个快餐分店、k 个客户（每个客户 (x,y)
//   需要 c 份餐）、d 个不能通行的格子。每份餐每走一格花费 1 元。
//   分店负责向所有客户送餐，求总花费最小是多少。
// 数据范围：1 <= n <= 1000，m, k, d <= n*n，总需求量 <= 1e6
// 思路：多源 BFS
//   如果每个客户单独找最近分店太慢；把"所有分店"同时作为起点做一次 BFS，
//   dist[x][y] = 到最近分店的距离（BFS 队列初始装所有分店）
//   答案 = Σ dist[客户] * 需求量
//   多源 BFS 与单源完全同构，只是起点有多个（等价于虚拟超级源点）
const int MAXN = 1005;
int n, m, k, d;
int dist[MAXN][MAXN];
bool block[MAXN][MAXN];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int main() {
    scanf("%d%d%d%d", &n, &m, &k, &d);
    memset(dist, -1, sizeof(dist));
    queue<pair<int, int> > q;
    for (int i = 0; i < m; i++) {               // 所有分店都是起点
        int x, y; scanf("%d%d", &x, &y);
        dist[x][y] = 0;
        q.push(make_pair(x, y));
    }
    while (d--) {                               // 障碍
        int x, y; scanf("%d%d", &x, &y);
        block[x][y] = true;
    }
    while (!q.empty()) {                        // 一次 BFS 求出每个格到最近分店距离
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int t = 0; t < 4; t++) {
            int nx = x + dx[t], ny = y + dy[t];
            if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
            if (block[nx][ny] || dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push(make_pair(nx, ny));
        }
    }
    ll ans = 0;
    for (int i = 0; i < k; i++) {
        int x, y, c; scanf("%d%d%d", &x, &y, &c);
        ans += (ll)dist[x][y] * c;              // 距离 * 份数
    }
    printf("%lld\n", ans);
    return 0;
}
// =====================================================================
#elif SOLVE == 8
// ============ 8. 洛谷 P1434 [SHOI2002] 滑雪 ============
// 题目内容：R x C 的矩阵，每个格有高度。从任一点出发，每次只能滑向
//   上下左右中高度严格更低的格子，求最长滑坡的长度（格数）。
// 数据范围：1 <= R, C <= 100，高度 <= 1e4
// 思路：记忆化搜索
//   dfs(i,j) = 从 (i,j) 出发的最长滑坡；dp[i][j] 存结果，-1 表示未算
//   由于只能往更低处滑，无环，直接递归：
//   dfs(i,j) = 1 + max(dfs(更低邻居))
//   记忆化把每个格只算一次，复杂度 O(R*C)
const int MAXN = 105;
int r, c, h[MAXN][MAXN], dp[MAXN][MAXN];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int dfs(int x, int y) {
    if (dp[x][y] != -1) return dp[x][y];   // 记忆化：算过直接返回
    dp[x][y] = 1;
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 1 || nx > r || ny < 1 || ny > c) continue;
        if (h[nx][ny] < h[x][y])           // 只能往更低处滑
            dp[x][y] = max(dp[x][y], dfs(nx, ny) + 1);
    }
    return dp[x][y];
}
int main() {
    scanf("%d%d", &r, &c);
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            scanf("%d", &h[i][j]);
    memset(dp, -1, sizeof(dp));
    int ans = 0;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            ans = max(ans, dfs(i, j));     // 起点任意
    printf("%d\n", ans);
    return 0;
}
// =====================================================================
#elif SOLVE == 9
// ============ 9. 洛谷 P4779 【模板】单源最短路径（标准版） ============
// 题目内容：n 个点 m 条边的有向带权图（边权非负），求 s 到每个点的
//   最短路，不可达输出 2^31-1（2147483647）。
// 数据范围：1 <= n <= 1e5，1 <= m <= 2e5，边权 <= 1e9
// 思路：Dijkstra 堆优化模板（T4 最高频算法之一，必须背熟）
//   每次从堆里取出 dist 最小的未确定点 u，用它松弛所有出边
//   惰性删除：pop 出的 dist 比记录的大说明是旧值，跳过
//   复杂度 O((n+m) log n)
const int MAXN = 100005;
const ll INF = 0x3f3f3f3f3f3f3f3fLL;
int n, m, s;
vector<pair<int, ll> > g[MAXN];            // (邻点, 边权)
ll dist[MAXN];
int main() {
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        scanf("%d%d%lld", &u, &v, &w);
        g[u].push_back(make_pair(v, w));
    }
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pair<ll, int>, vector<pair<ll, int> >,
                   greater<pair<ll, int> > > pq;   // 小顶堆 (dist, 点)
    dist[s] = 0;
    pq.push(make_pair(0LL, s));
    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;          // 惰性删除：旧记录
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i].first;
            ll w = g[u][i].second;
            if (dist[v] > dist[u] + w) {    // 松弛
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%lld ", dist[i] == INF ? 2147483647LL : dist[i]);
    printf("\n");
    return 0;
}
// =====================================================================
#elif SOLVE == 10
// ============ 10. CSP 201703-4 地铁修建 ============
// 题目内容：n 个交通枢纽，m 条可选隧道 (a, b, c)，c 是施工耗时。
//   要选一些隧道使 1 号枢纽能到 n 号枢纽（即连通），
//   总工期由所选隧道中最长的耗时决定，求这个值最小是多少。
// 数据范围：1 <= n <= 1e5，1 <= m <= 2e5，1 <= c <= 1e6
// 思路：Dijkstra 变体（最小瓶颈路）
//   把"路径长度"重新定义为路径上边的最大权值（瓶颈），
//   松弛操作从 dist[v] = min(dist[v], dist[u] + w)
//   改为  dist[v] = min(dist[v], max(dist[u], w))
//   其余框架与 Dijkstra 完全一致，堆按瓶颈值排序
//   第一次弹出 n 时 dist[n] 就是答案（瓶颈值随弹出单调不减）
//   等价解法：Kruskal 加边直到 1、n 连通
const int MAXN = 100005;
const int INF = 0x3f3f3f3f;
int n, m;
vector<pair<int, int> > g[MAXN];           // (邻点, 耗时)
int dist[MAXN];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a].push_back(make_pair(b, c));
        g[b].push_back(make_pair(a, c));
    }
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pair<int, int>, vector<pair<int, int> >,
                   greater<pair<int, int> > > pq;   // (瓶颈值, 点)
    dist[1] = 0;
    pq.push(make_pair(0, 1));
    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;
        if (u == n) { printf("%d\n", dist[n]); return 0; }  // 第一次弹出即最优
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i].first, w = g[u][i].second;
            int nd = max(dist[u], w);       // 关键：瓶颈取 max
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return 0;
}
// =====================================================================
#elif SOLVE == 11
// ============ 11. 洛谷 P1113 杂务 ============
// 题目内容：n 个杂务，每个杂务需要时间 t，且有一些前置杂务（完成后才能做）。
//   杂务之间可以并行进行，求完成所有杂务所需的最短时间。
//   输入：每行一个杂务 i：编号 时间t 前置编号... 0（0 表示前置列表结束）。
// 数据范围：1 <= n <= 1e5
// 思路：拓扑排序（Kahn 算法）+ DP
//   建边：前置 p -> 当前 i（p 做完才能做 i），入度 = 前置个数
//   入度为 0 的任务可以直接开始，放入队列
//   每次取出任务 u，松弛其后继 v：dp[v] = max(dp[v], dp[u] + t[v])
//   dp[v] = 任务 v 的最早完成时间；答案 = 所有 dp 的最大值
//   Kahn = BFS 版拓扑排序：入度为 0 入队，出队时把后继入度 -1
const int MAXN = 100005;
int n, t[MAXN], in[MAXN], dp[MAXN];
vector<int> g[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int id, tt;
        scanf("%d%d", &id, &tt);
        t[id] = tt;
        int p;
        while (scanf("%d", &p) && p) {      // 前置列表，0 结束
            g[p].push_back(id);             // 前置 p -> 当前 id
            in[id]++;
        }
    }
    queue<int> q;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (in[i] == 0) { dp[i] = t[i]; q.push(i); }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ans = max(ans, dp[u]);
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            dp[v] = max(dp[v], dp[u] + t[v]);
            if (--in[v] == 0) q.push(v);    // 前置全部完成
        }
    }
    printf("%d\n", ans);
    return 0;
}
// =====================================================================
#elif SOLVE == 12
// ============ 12. 洛谷 P4017 最大食物链计数 ============
// 题目内容：n 个生物组成食物网，m 条捕食关系。
//   食物链：从生产者（只被捕食、不捕食）到最高级消费者（只捕食）的路径。
//   求食物网中食物链的总条数，对 80112002 取模。
// 数据范围：1 <= n <= 5e5，1 <= m <= 5e5
// 思路：拓扑排序 + 计数 DP（路径条数问题）
//   输入 a b 表示 a 捕食 b，能量从被捕食者流向捕食者：建边 b -> a
//   生产者 = 入度 0（不被任何生物吃），顶级消费者 = 出度 0
//   dp 沿拓扑序累加：dp[v] = (dp[v] + dp[u]) % MOD（u 的能量流向 v）
//   答案 = 所有出度 0 的点 dp 之和
const int MAXN = 500005;
const int MOD = 80112002;
int n, m, in[MAXN], out[MAXN];
ll dp[MAXN];
vector<int> g[MAXN];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);             // a 捕食 b
        g[b].push_back(a);                 // 能量方向：b -> a
        in[a]++; out[b]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (in[i] == 0) { dp[i] = 1; q.push(i); }  // 生产者是链的起点
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            dp[v] = (dp[v] + dp[u]) % MOD;
            if (--in[v] == 0) q.push(v);
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        if (out[i] == 0) ans = (ans + dp[i]) % MOD;  // 顶级消费者收尾
    printf("%lld\n", ans);
    return 0;
}
// =====================================================================
#elif SOLVE == 13
// ============ 13. 洛谷 P3956 [NOIP2017 普及组] 棋盘（0-1 BFS） ============
// 题目内容：m x m 棋盘，从 (1,1) 走到 (m,m)。格子有颜色 0/1 或无颜色。
//   同色移动花 0 金币，异色花 1 金币；走到无色格可用魔法花 2 金币
//   （把格子变成当前颜色），魔法不能连续使用。求最少金币，无解输出 -1。
// 数据范围：1 <= m <= 100
// 思路：0-1 BFS（双端队列）
//   状态 (x, y, color)，dist 三维。
//   边的花费只有 0 和 1（同色 0 / 异色 1），
//   Dijkstra 的堆可以用 deque 代替：
//     花费 0 的边 -> push_front，花费 1（或魔法 2）的边 -> push_back
//   队列里 dist 始终保持"非降且差 <= 1"，第一次取出即为最短路
//   魔法（花 2）也放队尾即可（本题数据下正确；严格含边权 2 的题
//   建议直接用 Dijkstra，0-1 BFS 只对边权 {0,1} 严格成立）
用dijskra最好
const int MAXN = 105;
const int INF = 0x3f3f3f3f;
int m, n, g[MAXN][MAXN];
int dist[MAXN][MAXN][2];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
struct Node { int x, y, c; };
int main() {
    scanf("%d%d", &m, &n);
    memset(g, -1, sizeof(g));               // -1 = 无色
    for (int i = 0; i < n; i++) {
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        g[x][y] = c;
    }
    memset(dist, 0x3f, sizeof(dist));
    deque<Node> dq;
    if (g[1][1] != -1) {                    // 起点有色
        dist[1][1][g[1][1]] = 0;
        dq.push_back((Node){1, 1, g[1][1]});
    } else {                                // 起点无色：先变魔法（花 2）
        dist[1][1][0] = dist[1][1][1] = 2;
        dq.push_back((Node){1, 1, 0});
        dq.push_back((Node){1, 1, 1});
    }
    while (!dq.empty()) {
        Node t = dq.front(); dq.pop_front();
        for (int k = 0; k < 4; k++) {
            int nx = t.x + dx[k], ny = t.y + dy[k];
            if (nx < 1 || nx > m || ny < 1 || ny > m) continue;
            if (g[nx][ny] != -1) {          // 目标格有色
                int cost = (g[nx][ny] == t.c ? 0 : 1);
                if (dist[nx][ny][g[nx][ny]] > dist[t.x][t.y][t.c] + cost) {
                    dist[nx][ny][g[nx][ny]] = dist[t.x][t.y][t.c] + cost;
                    if (cost == 0) dq.push_front((Node){nx, ny, g[nx][ny]});
                    else           dq.push_back ((Node){nx, ny, g[nx][ny]});
                }
            } else {                        // 目标格无色：使用魔法
                if (dist[nx][ny][t.c] > dist[t.x][t.y][t.c] + 2) {
                    dist[nx][ny][t.c] = dist[t.x][t.y][t.c] + 2;
                    dq.push_back((Node){nx, ny, t.c});   // 颜色保持
                }
            }
        }
    }
    int ans = min(dist[m][m][0], dist[m][m][1]);
    printf("%d\n", ans >= INF ? -1 : ans);
    return 0;
}

// =====================================================================
#elif SOLVE == 14
// ============ 14. 洛谷 P4799 [CEOI2015 Day2] 世界冰球锦标赛 ============
// 题目内容：N 场比赛，每场票价 a[i]，共有 M 元预算。求有多少种看比赛
//   的方案（每种方案 = 选若干场，总票价不超过 M）。
// 数据范围：1 <= N <= 40，M, a[i] <= 1e18
// 思路：折半搜索 meet in the middle
//   直接枚举所有子集是 2^40，不可行。
//   把比赛分成两半（各 20 场），分别枚举每半的所有子集花费：
//   两个 2^20 的列表 s1, s2
//   对 s1 中每个花费 x，求 s2 中有多少 <= M - x（二分查找），累加
//   复杂度 O(2^(N/2) log 2^(N/2)) = O(2^20 * 20)，可行
//   技巧：枚举子集和用 DFS（选/不选），花费超 M 直接剪枝
int n;
ll m, a[45];
vector<ll> s1, s2;
void dfs(int l, int r, ll sum, vector<ll>& v) {
    if (sum > m) return;                    // 剪枝：已超预算
    if (l > r) { v.push_back(sum); return; }
    dfs(l + 1, r, sum, v);                  // 不选 l
    dfs(l + 1, r, sum + a[l], v);           // 选 l
}
int main() {
    scanf("%d%lld", &n, &m);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    int mid = n / 2;
    dfs(0, mid - 1, 0, s1);                 // 前半所有子集和
    dfs(mid, n - 1, 0, s2);                 // 后半所有子集和
    sort(s2.begin(), s2.end());
    ll ans = 0;
    for (size_t i = 0; i < s1.size(); i++)
        ans += upper_bound(s2.begin(), s2.end(), m - s1[i]) - s2.begin();
    printf("%lld\n", ans);
    return 0;
}
// =====================================================================
#elif SOLVE == 15
// ============ 15. 洛谷 P1379 八数码难题 ============
// 题目内容：3 x 3 棋盘上有 8 个数码（1..8）和一个空位（0），
//   空位可向上下左右移动（与相邻数码交换）。给定初始状态，求变成
//   目标状态 123804765 的最少步数。
// 思路：A* = BFS + 估价函数
//   估价 h(s) = 每个数码到目标位置的曼哈顿距离之和（可采纳：不会高估）
//   优先队列按 f = g + h 排序（g = 已走步数），先扩展最有希望的状态
//   与普通 BFS 唯一区别：队列换成按 f 排序的堆
//   第一次扩展到目标状态时 g 就是最优解
//   状态用字符串存，unordered_map 存每个状态的最小 g
const int goal_pos[9][2] = {              // 数字 1..8 的目标坐标，0 不用
    {0, 0}, {0, 0}, {0, 1}, {0, 2},       // 数字 1..3
    {1, 0}, {1, 1}, {1, 2},               // 数字 4..6
    {2, 0}, {2, 1}                        // 数字 7..8
};
int h(const string& s) {                  // 曼哈顿距离和
    int res = 0;
    for (int i = 0; i < 9; i++) {
        if (s[i] == '0') continue;
        int v = s[i] - '0';
        res += abs(i / 3 - goal_pos[v][0]) + abs(i % 3 - goal_pos[v][1]);
    }
    return res;
}
struct Node { int f, g; string s;
    bool operator<(const Node& o) const { return f > o.f; }  // 小顶堆
};
int main() {
    string start;
    cin >> start;
    const string goal = "123804765";
    priority_queue<Node> pq;
    unordered_map<string, int> gd;
    gd[start] = 0;
    pq.push((Node){h(start), 0, start});
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    while (!pq.empty()) {
        Node t = pq.top(); pq.pop();
        if (t.g > gd[t.s]) continue;        // 惰性删除
        if (t.s == goal) { printf("%d\n", t.g); return 0; }
        int p = t.s.find('0'), x = p / 3, y = p % 3;
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx > 2 || ny < 0 || ny > 2) continue;
            string s2 = t.s;
            swap(s2[p], s2[nx * 3 + ny]);
            int ng = t.g + 1;
            if (!gd.count(s2) || ng < gd[s2]) {
                gd[s2] = ng;
                pq.push((Node){ng + h(s2), ng, s2});
            }
        }
    }
    return 0;
}
// =====================================================================
#endif
