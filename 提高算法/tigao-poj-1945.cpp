#include<cstdio>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
struct Node{
    int a,b,g,h;
    Node(int a,int b,int g,int h):a(a),b(b),g(g),h(h){}
    bool operator<(const Node&rhs)const{return g+h>rhs.g+rhs.h;}
};
int P;
const int LIMIT=100000;
int calc_h(int a,int b){
    int m=max(a,b);
    if(m>=P)return 0;
    int cnt=0;
    while(m<P){m<<=1;cnt++;}
    return cnt;
}
int astar(){
    if(P==1)return 0;
    priority_queue<Node>pq;
    map<pair<int,int>,int>best;
    int h0=calc_h(1,0);
    pq.push(Node(1,0,0,h0));
    best[{1,0}]=0;
    while(!pq.empty()){
        Node cur=pq.top();pq.pop();
        int a=cur.a,b=cur.b,g=cur.g;
        if(a==P||b==P)return g;
        auto it=best.find({a,b});
        if(it!=best.end()&&it->second<g)continue;
        int next_states[8][2]={
            {2*a,b},{a,2*a},
            {2*b,b},{a,2*b},
            {a+b,b},{a,a+b},
            {abs(a-b),b},{a,abs(a-b)}
        };
        for(int i=0;i<8;i++){
            int na=next_states[i][0];
            int nb=next_states[i][1];
            if(na>LIMIT||nb>LIMIT)continue;
            int ng=g+1;
            if(na==P||nb==P)return ng;
            pair<int,int>key={na,nb};
            auto iter=best.find(key);
            if(iter==best.end()||ng<iter->second){
                best[key]=ng;
                int nh=calc_h(na,nb);
                pq.push(Node(na,nb,ng,nh));
            }
        }
    }
    return -1;
}
int main(){
    scanf("%d",&P);
    printf("%d\\n",astar());
    return 0;
}
