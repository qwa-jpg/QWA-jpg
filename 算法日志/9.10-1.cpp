// 洛谷 P2679 子串（NOIP 2015 提高组 D2T2）
// 思路：四维 DP + 滚动数组
//   dp[i][j][k][0/1]
//     i：扫到 A 的第 i 个字符
//     j：匹配到 B 的第 j 个字符
//     k：已经用了 k 段子串
//     0：A[i] 未参与匹配；1：A[i] 参与（作为当前段结尾）
//   转移：
//     A[i]==B[j] 时：
//       dp[1] = 延续上一段 + 新开一段（前一位用/不用）
//     A[i]!=B[j] 时：dp[1] = 0
//     dp[0] 恒为继承前 i-1 个字符的结果
//   答案：dp[|A|][|B|][K][0] + dp[|A|][|B|][K][1]
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int dp[2][205][205][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, K;
    string A, B;
    cin >> n >> m >> K >> A >> B;
    A = " " + A;
    B = " " + B;

    int pre = 0, cur = 1;
    dp[pre][0][0][0] = 1; // 空串：取 0 段，1 种方案

    for (int i = 1; i <= n; i++) {
        memset(dp[cur], 0, sizeof(dp[cur]));
        dp[cur][0][0][0] = 1;

        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= K; k++) {
                if (A[i] == B[j]) {
                    // 延续上一段 + 新开一段（前一位用/不用）
                    dp[cur][j][k][1] =
                        ((long long)dp[pre][j - 1][k][1] +
                         dp[pre][j - 1][k - 1][0] +
                         dp[pre][j - 1][k - 1][1]) % MOD;
                }
                // A[i] 不用：继承前 i-1 个字符的结果
                dp[cur][j][k][0] = (dp[pre][j][k][0] + dp[pre][j][k][1]) % MOD;
            }
        }
        swap(pre, cur);
    }

    cout << (dp[pre][m][K][0] + dp[pre][m][K][1]) % MOD << "\\\\n";
    return 0;
}
