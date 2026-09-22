// =====================================================================
// 洛谷 P1908 逆序对
// 思路：离散化 + 树状数组
//   1. 先读入全部数据（离散化需要知道所有值），排序去重得到排名
//   2. 然后从左到右逐个插入（在线统计）：
//      · query(rank)：已插入的、值 <= a[i] 的元素个数
//        （相等值离散化后排名相同，会被一并计入，所以不会被误算为逆序对）
//      · 前面已插入 i 个，因此 > a[i] 的个数 = i - query(rank)
//      · add(rank, 1)：树状数组中对应 lowbit 逐级 +1 直到边界 n
// 答案用 long long（最坏 n(n-1)/2 ≈ 1.25e11，int 会溢出）
// 复杂度 O(n log n)，n <= 5e5 轻松通过
// =====================================================================
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 500005;
int n, tree[MAXN];

int lowbit(int x) { return x & -x; }

// 单点更新：i 及其管辖它的祖先都 +v
void add(int i, int v) {
    for (; i <= n; i += lowbit(i)) tree[i] += v;
}

// 前缀和查询：1..i 的和
int query(int i) {
    int s = 0;
    for (; i > 0; i -= lowbit(i)) s += tree[i];
    return s;
}

int main() {
    scanf("%d", &n);
    vector<int> a(n), b;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b.push_back(a[i]);
    }

    // 离散化：排序 + 去重，rank 从 1 开始
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int rank = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
        ans += (ll)i - query(rank);   // 前面插入的 i 个里，减去 <= a[i] 的，即严格大于的个数
        add(rank, 1);                 // 把当前值插进树状数组
    }
    printf("%lld\n", ans);
    return 0;
}
