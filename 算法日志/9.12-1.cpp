/*以下是图片中提取的题目文字：

例 4.2 How many answers are wrong (hdu 3038)

问题描述：给出区间[a, b]，区间和为v。输入m组数据，每输入一组，判断此组条件是否与前面冲突，最后输出与前面冲突的数据的个数。例如，先给出区间[1, 5]，区间和为100；再给出区间[1, 2]，区间和为200；区间[3, 5]，区间和为-500，肯定有冲突。

输入：第1行输入两个整数n和m(1≤n≤200000, 1≤m≤40000)，表示n个整数，m组数据。第2~m+1行中，每行输入3个整数a_i, b_i, v_i，表示[a_i, b_i]区间和为v_i，0≤a_i≤b_i≤n。

输出：输出一个整数，表示冲突数据的个数。*/
// 例 4.2 How many answers are wrong (hdu 3038)
// 带权并查集：维护前缀和关系 s[b] - s[a] = v
//   区间和 [a,b] = v  <==>  s[b] - s[a-1] = v，故合并时传入 a-1
//   d[x] = s[fa[x]] - s[x]，即 x 到其父节点的"前缀和差"
//   同根时检验 d[a] - d[b] == v（即 s[b] - s[a] == v）
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
int n, m;
int fa[MAXN];
int d[MAXN]; // 权值，记录 s[fa[x]] - s[x]（s 为前缀和）
int ans;

void init_set() {
    for(int i = 0; i <= n; i++) { fa[i] = i; d[i] = 0; }
}

int find_set(int x) {
    if(x != fa[x]) {
        int t = fa[x];              // 记录父节点
        fa[x] = find_set(fa[x]);    // 路径压缩，递归最后返回的是根节点
        d[x] += d[t];               // 权值更新为 x 到根节点的权值
    }
    return fa[x];
}

void merge_set(int a, int b, int v) {
    int roota = find_set(a), rootb = find_set(b);
    if(roota == rootb) {
        if(d[a] - d[b] != v) ans++; // 同根：检验 s[b] - s[a] 是否等于 v
    } else {
        fa[roota] = rootb;          // 合并
        d[roota] = d[b] - d[a] + v; // 使 s[b] - s[a] = v 成立
    }
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        init_set();
        ans = 0;
        while(m--) {
            int a, b, v;
            scanf("%d%d%d", &a, &b, &v);
            merge_set(a - 1, b, v); // 关键修正：区间和 [a,b]=v 对应前缀 s[b]-s[a-1]=v
        }
        printf("%d\n", ans);
    }
    return 0;
}
