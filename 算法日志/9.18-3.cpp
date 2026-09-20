// 积水问题（接雨水 II）
// 地面上 W 列 x H 行砖块（3<=W,H<=300，砖高 B 满足 1<=B<=1e9）
// 求雨后这块地面能容纳多少水（水会从场地四周流走）
// 输入格式：第一行 W H，接下来 H 行每行 W 个整数（砖高）
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int main() {
    int W, H;
    scanf("%d%d", &W, &H);
    vector<vector<int> > h(H, vector<int>(W));
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            scanf("%d", &h[i][j]);

    // 小根堆：存 (瓶颈高度, 行, 列)
    priority_queue<pair<int, pair<int, int> >,
                   vector<pair<int, pair<int, int> > >,
                   greater<pair<int, pair<int, int> > > > pq;
    vector<vector<char> > vis(H, vector<char>(W, 0));

    // 边界格：水从这里流走，水位 = 自身砖高，全部入堆
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (i == 0 || i == H - 1 || j == 0 || j == W - 1) {
                pq.push(make_pair(h[i][j], make_pair(i, j)));
                vis[i][j] = 1;
            }

    ll ans = 0;
    while (!pq.empty()) {
        int cur = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();
        // cur：从边界漫到 (x,y) 的路径上的最大砖高（最小瓶颈）
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx >= H || ny < 0 || ny >= W || vis[nx][ny]) continue;
            vis[nx][ny] = 1;
            // 邻居砖高低于当前水位 -> 可积水
            if (cur > h[nx][ny]) ans += (ll)cur - h[nx][ny];
            pq.push(make_pair(max(cur, h[nx][ny]), make_pair(nx, ny)));
        }
    }
    printf("%lld\n", ans);
    return 0;
}
