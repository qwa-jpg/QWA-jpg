# include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, M = 2e6 + 5; //100万个点,200万条边
int cnt = 0, head[N];                //cnt等于其他值也行,根据题目要求赋值
struct {int to, next, w;} edge[M];
void addedge(int u, int v, int w) {
    cnt++;
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt;
}
int main() {
    int n, m; cin>>n>>m;
    for(int i = 0; i < m; i++){int u, v, w; cin>>u>>v>>w; addedge(u, v, w);}
    for(int i = head[2]; i > 0; i = edge[i].next) //遍历节点2的所有邻居
        printf("%d ", edge[i].to);        //输出：5 4 3 1
    return 0;
}
