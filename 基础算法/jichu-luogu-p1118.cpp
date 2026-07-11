#include<bits/stdc++.h>
using namespace std;
int N, target;
int coeff[13];
bool used[13];
int seq[13];

bool canAchieve(int pos, int curSum) {
    int remainNums[13], remainCoeff[13];
    int cnt = 0;
    for (int i = 1; i <= N; ++i)
        if (!used[i]) remainNums[cnt++] = i;
    for (int i = pos + 1; i < N; ++i)
        remainCoeff[i - (pos + 1)] = coeff[i];
    int minAdd = 0, maxAdd = 0;
    for (int i = 0; i < cnt; ++i) {
        minAdd += remainNums[i] * remainCoeff[cnt - 1 - i];
        maxAdd += remainNums[i] * remainCoeff[i];
    }
    return curSum + minAdd <= target && curSum + maxAdd >= target;
}
void dfs(int pos, int curSum) {
    if (pos == N) {
        if (curSum == target) {
            for (int i = 0; i < N; ++i)
                printf("%d%c", seq[i], i == N - 1 ? '\n' : ' ');
            exit(0);
        }
        return;
    }
    for (int num = 1; num <= N; ++num) {
        if (used[num]) continue;
        used[num] = true;
        seq[pos] = num;
        int nextSum = curSum + num * coeff[pos];
        if (canAchieve(pos, nextSum)) {
            dfs(pos + 1, nextSum);
        }
        used[num] = false;
    }
}
int main() {
    scanf("%d %d", &N, &target);
    
    coeff[0] = 1;
    for (int i = 1; i < N; ++i) {
        coeff[i] = coeff[i - 1] * (N - i) / i;
    }
    dfs(0, 0);
    return 0;
}
//算法思路：优化：用先算系数和剪枝，通过最大排列实现舍去的；coeff为系数
