/*
 * 小木棍（洛谷 P1120）
 *
 * 题意：乔治有若干根等长的原始木棍，被随意砍成 n 段（每段 <= 50）。
 *       给定 n 段的长度（n <= 65），求原始木棍的最小可能长度。
 *
 * 思路：枚举答案 L + DFS 回溯 + 剪枝。
 *   1. 总长 sum 不变，L 必须是 sum 的约数，且 L >= 最长的一段。
 *   2. 段按从大到小排序，从长到短尝试（先放大段，失败得快）。
 *   3. DFS：一根一根拼原始木棍，每根内从大到小选段。
 *   四大剪枝（缺一不可，否则 n=65 会超时）：
 *   (1) 同长剪枝：某长度的段试过失败后，同一位置不再试等长的段；
 *   (2) 头段剪枝：某根木棍的第一段（当前最长未用段）放进去就失败，
 *       则该 L 无解——这根长段无论如何都要被放下，放第一根位置等价；
 *   (3) 尾段剪枝：某段恰好拼满当前木棍、但后续拼不完，则此分支失败——
 *       用几根更短的段替换它不会更优（交换论证）；
 *   (4) 后缀和剪枝：剩余可用段总长 < 还需拼的长度，直接失败。
 *
 * 复杂度：指数级最坏，但剪枝后 n<=65 可快速出解（本题经典结论）。
 *
 * 输入格式：第一行 n，第二行 n 个整数（每段长度）。
 * 输出格式：一行一个整数（最小原始长度）。
 */
#include <bits/stdc++.h>
using namespace std;

int n, a[70], total, len, cnt;   // len: 当前枚举的原始长度; cnt: 应有根数
bool used[70];
int suf[70];                     // 后缀和：a[i..n-1] 的长度总和

// 已拼好 idx 根，当前这根已拼 cur 长，从下标 st 开始尝试选段
bool dfs(int idx, int cur, int st) {
    if (idx == cnt) return true;              // 所有原始木棍都拼好
    if (cur == len) return dfs(idx + 1, 0, 0); // 这根拼满，拼下一根
    if (suf[st] < len - cur) return false;    // 剪枝(4)：剩余段不够拼
    int last = 0;
    for (int i = st; i < n; i++) {
        if (used[i] || cur + a[i] > len || a[i] == last) continue;
        used[i] = true;
        if (dfs(idx, cur + a[i], i + 1)) return true;
        used[i] = false;
        last = a[i];                          // 剪枝(1)：等长段不再试
        if (cur == 0) return false;           // 剪枝(2)：第一段失败
        if (cur + a[i] == len) return false;  // 剪枝(3)：恰好拼满仍失败
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        total += a[i];
    }
    sort(a, a + n, greater<int>());           // 从大到小
    for (int i = n - 1; i >= 0; i--)
        suf[i] = suf[i + 1] + a[i];

    for (len = a[0]; len <= total; len++) {   // L 至少为最长段
        if (total % len) continue;            // 必须是总长的约数
        cnt = total / len;
        memset(used, 0, sizeof(used));
        if (dfs(0, 0, 0)) break;              // 第一个可行 L 就是最小
    }
    printf("%d\n", len);
    return 0;
}
