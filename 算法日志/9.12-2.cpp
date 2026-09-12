// 例 4.3 食物链 (poj 1182)
// 问题描述：动物王国中有 3 类动物 A、B、C，食物链：A 吃 B，B 吃 C，C 吃 A。
//   现有 N 个动物(编号 1~N)，每只属于 A/B/C 之一但未知。有人用两种说法描述：
//   说法 1 "1 X Y"：X 和 Y 是同类；说法 2 "2 X Y"：X 吃 Y。
//   一句话为假话当且仅当满足以下条件之一：
//   (1) 与前面的某些真话冲突；(2) X 或 Y 比 N 大；(3) 说法 2 且 X==Y（自己吃自己）。
// 输入：第 1 行两个整数 N(1≤N≤50000) 和 K(0≤K≤100000)。以下 K 行每行 3 个正整数 D、X、Y。
// 输出：假话的总数。
// 思路：带权并查集。d[] 记录两个动物在食物链上的相对关系：
//   d(A→B)=0 表示同类，=1 表示 A 吃 B，=2 表示 A 被 B 吃。
//   关系可传递：d(A→C) = (d(A→B) + d(B→C)) % 3，故权值更新为累加取模 3。
#include <iostream>
#include <stdio.h>
using namespace std;
const int N = 50005;
int s[N];                 // 集
int d[N];                 // 0: 同类; 1: 吃; 2: 被吃
int ans;
void init_set() {         // 初始化
    for(int i = 0; i <= N; i++) { s[i] = i; d[i] = 0; }
}
int find_set(int x) {     // 带权值的路径压缩
    if(x != s[x]) {
        int t = s[x];          // 记录父节点
        s[x] = find_set(s[x]); // 路径压缩，递归最后返回的是根节点
        d[x] = (d[x] + d[t]) % 3; // 权值更新为 x 到根节点的权值
    }
    return s[x];
}
void merge_set(int x, int y, int relation) { // 合并
    int rootx = find_set(x); int rooty = find_set(y);
    if (rootx == rooty) {
        if ((relation - 1) != ((d[x] - d[y] + 3) % 3)) // 判断矛盾
            ans++;
    }
    else {                    // 合并
        s[rootx] = rooty;     // 更新权值
        d[rootx] = (d[y] - d[x] + relation - 1 + 3) % 3; // +3 保证结果非负
    }
}
int main() {
    int n, k; cin >> n >> k;
    init_set();
    ans = 0;
    while (k--) {
        int relation, x, y; scanf("%d%d%d", &relation, &x, &y);
        if( x > n || y > n || (relation == 2 && x == y) ) ans++;
        else merge_set(x, y, relation);
    }
    cout << ans;
    return 0;
}
