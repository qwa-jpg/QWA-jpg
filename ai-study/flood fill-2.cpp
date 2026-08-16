/*
 * 引水入城（NOIP 2010 提高组 / 洛谷 P1514）
 *
 * 题意：N 行 M 列城市，第一行临湖、最后一行临沙漠。可在第一行城市建蓄水厂，
 *       水只能向相邻且海拔严格更低的城市流。问能否让每个沙漠城市都有水：
 *       能   -> 第一行输出 1，第二行输出最少蓄水厂数；
 *       不能 -> 第一行输出 0，第二行输出无法供水的沙漠城市数。
 *
 * 思路：
 *   1. 从第一行每个城市 BFS（水向严格更低的相邻格流），
 *      得到它能供水的最后一行城市集合。
 *   2. 若所有源点并集没有覆盖全部最后一行城市 -> 输出 0 和未覆盖数。
 *   3. 关键引理：第一行任一城市可达的最后一行城市构成一段连续区间。
 *      （直观证明：若可达 x、z (x<z) 而不可达 y (x<y<z)，则到 x、到 z 的
 *       两条下坡路径与底边围成一个封闭区域，y 在底边上；由"水往低处流"
 *       可推出区域边界高度关系的矛盾，故 y 必可达。此为本题经典结论，
 *       竞赛中可直接引用。）
 *      因此每个源点只需记录最左/最右可达列 [L, R]。
 *   4. 化为经典区间覆盖：用最少的区间覆盖 [0, M-1]。
 *      贪心：区间按左端点排序，每次在所有能接上的区间中选右端点最远的。
 *
 * 复杂度：M 次 BFS x O(NM) = O(NM^2)，最坏 500 x 500^2 = 1.25e8，可过。
 *
 * 输入格式：第一行 N M，接下来 N 行每行 M 个海拔。
 * 输出格式：两行。
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
int n, m;
int h[MAXN][MAXN];
int L[MAXN], R[MAXN];          // 第一行第 s 列城市能供水的最后一行列区间
bool vis[MAXN][MAXN];

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

// 从第一行城市 (0, s) 出发 BFS，水只能流向相邻且海拔严格更低的城市
void bfs(int s) {
    memset(vis, 0, sizeof(vis));
    queue<pair<int, int> > q;
    vis[0][s] = true;
    q.push(make_pair(0, s));
    int l = m + 1, r = -1;     // 能到达的最后一行最左/最右列
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        if (x == n - 1) {      // 到达最后一行（沙漠城市）
            l = min(l, y);
            r = max(r, y);
        }
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (!vis[nx][ny] && h[nx][ny] < h[x][y]) {   // 严格更低才流
                vis[nx][ny] = true;
                q.push(make_pair(nx, ny));
            }
        }
    }
    L[s] = l;
    R[s] = r;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &h[i][j]);

    // 1) 判定：所有沙漠城市是否都能被供水
    vector<char> cover(m, 0);
    for (int s = 0; s < m; s++) {
        bfs(s);
        // 引理保证 [L[s], R[s]] 内的最后一行城市全部可达
        for (int j = L[s]; j <= R[s]; j++) cover[j] = 1;
    }
    int cnt = 0;
    for (int j = 0; j < m; j++) cnt += !cover[j];
    if (cnt > 0) {
        printf("0\n%d\n", cnt);
        return 0;
    }

    // 2) 区间覆盖贪心：最少区间覆盖 [0, m-1]
    vector<pair<int, int> > iv;
    for (int s = 0; s < m; s++)
        if (L[s] <= R[s])                    // 跳过供不了水的源点
            iv.push_back(make_pair(L[s], R[s]));
    sort(iv.begin(), iv.end());              // 按左端点排序

    int ans = 0, cur = -1, i = 0;            // cur: 已覆盖到第几列
    while (cur < m - 1) {
        int best = -1;
        while (i < (int)iv.size() && iv[i].first <= cur + 1) {
            best = max(best, iv[i].second);  // 能接上的区间里取右端点最远
            i++;
        }
        cur = best;                          // 全可达保证 best != -1
        ans++;
    }
    printf("1\n%d\n", ans);
    return 0;
}
