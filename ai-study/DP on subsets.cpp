/*
 * ============================================================
 *   Mondriaan's Dream（POJ 2411）铺砖问题
 * ============================================================
 * 【问题】用 1x2 的骨牌铺满 H x W 的网格，求方案数。
 *   输入多组 H W，以 "0 0" 结束。H, W <= 11。
 *
 * 【思路】轮廓线/逐行状压 DP：
 *   dp[i][s] = 前 i-1 行已铺满，第 i 行中"被上一行竖放的骨牌凸出
 *              覆盖"的格子集合为 s 的方案数（s 的第 j 位 = 1 表示
 *              第 i 行第 j 列已被上一行占住）。
 *   对每一行，枚举上一行凸出状态 pre，DFS 枚举当前行的铺法，
 *   生成向下一行凸出的状态 cur，累加到 dp[i+1][cur]。
 *
 * 【DFS 的三种情况】（决策当前行的第 col 列）：
 *   情况1：pre 第 col 位 = 1 —— 该格已被上一行竖放覆盖，只能跳过。
 *          写法：dfs(col + 1, pre, cur)，cur 不变。
 *   情况2：横放一块 —— 占当前行 col、col+1 两格，不向下一行凸出。
 *          要求 col+1 < W 且 pre 第 col+1 位 = 0（两格都不能被占）。
 *          写法：dfs(col + 2, pre, cur)。
 *   情况3：竖放一块 —— 占当前行 col 格，凸出到下一行第 col 格。
 *          写法：dfs(col + 1, pre, cur | (1 << col))。
 *
 * 【复杂度】O(H * W * 2^W)，W 取较小的边（先 swap）以减小状态数。
 * 【样例】2x2 -> 2；2x3 -> 3；2x4 -> 5（Fibonacci）。
 * ============================================================
 */
#include <cstdio>
#include <cstring>
using namespace std;

int H, W;                        // 行数 H、列数 W（保证 W <= H）
long long dp[13][1 << 11];       // dp[i][s]：前 i-1 行铺满、第 i 行凸出状态为 s 的方案数

// 当前铺第 row 行，正在决策第 col 列：
//   pre : 上一行竖放凸进当前行的状态（1 = 该格已被覆盖）
//   cur : 当前行竖放凸进下一行的状态（1 = 下一行该格将被覆盖）
void dfs(int row, int col, int pre, int cur) {
    if (col == W) {                          // 当前行全部铺完
        dp[row + 1][cur] += dp[row][pre];    // 方案数累加给下一行
        return;
    }
    if ((pre >> col) & 1) {                  // 情况1：该格已被上一行覆盖
        dfs(row, col + 1, pre, cur);         //   只能跳过
        return;
    }
    // 情况2：横放，占 col、col+1 两格
    if (col + 1 < W && !((pre >> (col + 1)) & 1))
        dfs(row, col + 2, pre, cur);
    // 情况3：竖放，凸出到下一行 col 格
    dfs(row, col + 1, pre, cur | (1 << col));
}

int main() {
    while (~scanf("%d%d", &H, &W) && (H || W)) {
        if (H < W) swap(H, W);               // 让 W 较小，状态数 2^W 更少
        memset(dp, 0, sizeof(dp));
        dp[1][0] = 1;                        // 第 1 行上方没有凸出
        for (int i = 1; i <= H; i++)
            for (int s = 0; s < (1 << W); s++)
                if (dp[i][s])
                    dfs(i, 0, s, 0);
        printf("%lld\n", dp[H + 1][0]);      // 铺满 H 行且不凸出到 H+1 行
    }
    return 0;
}
