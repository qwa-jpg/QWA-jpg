// 洛谷 P1525 [NOIP 2010 提高组] 关押罪犯
// 思路：贪心 + 并查集（存"怨恨值最大的敌人"）
//   按怨气值从大到小排序，逐条处理仇恨边 (a, b)：
//   - 若 find(a) == find(b)：a、b 已被迫关在同一监狱，当前怨气值就是答案；
//   - 否则把 b 与 a 的敌人拼在一起（b 和 a 的所有敌人必须同监狱），
//     同样把 a 与 b 的敌人拼在一起。
//   由于降序处理，每个罪犯第一次遇到的敌人就是怨恨值最大的敌人，
//   所以 enemy[x] 只存一个点即可。
//   全部处理完都无冲突，输出 0。
#include <bits/stdc++.h>
using namespace std;

const int N = 20005;

struct Edge {
    int a, b, c;
    bool operator<(const Edge& o) const { return c > o.c; }
} e[100005];

int fa[N], enemy[N];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        cin >> e[i].a >> e[i].b >> e[i].c;

    sort(e, e + m);                    // 怨气值降序

    for (int i = 1; i <= n; i++)
        fa[i] = i;

    for (int i = 0; i < m; i++) {
        int a = e[i].a, b = e[i].b;
        if (find(a) == find(b)) {      // 被迫同监狱，冲突无法避免
            cout << e[i].c << '\n';
            return 0;
        }
        if (!enemy[a]) enemy[a] = b;   // 记录怨恨值最大的敌人
        else merge(b, enemy[a]);       // b 必须和 a 的敌人同监狱
        if (!enemy[b]) enemy[b] = a;
        else merge(a, enemy[b]);
    }

    cout << 0 << '\n';                 // 全程无冲突
    return 0;
}
