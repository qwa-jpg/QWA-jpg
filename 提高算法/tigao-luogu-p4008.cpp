#include<bits/stdc++.h>
using namespace std;
int block=2500;
list<vector<char>> List;
typedef list<vector<char>>::iterator it;
it Find(int&pos){
    for(it i=List.begin();;i++){
        if(i==List.end()||pos<=i->size())return i;
        pos-=i->size();
    }
}
void Output(int L,int R){
    it L_block=Find(L),R_block=Find(R);
    for(it it1=L_block;;it1++){
        int a;it1==L_block?a=L:a=0;
        int b;it1==R_block?b=R:b=it1->size();
        for(int i=a;i<b;i++)putchar(it1->at(i));
        if(it1==R_block)break;
    }
    putchar('\n');
}
it Next(it x){return ++x;}
void Merge(it x){
    x->insert(x->end(),Next(x)->begin(),Next(x)->end());
    List.erase(Next(x));
}
void Split(it x,int pos){
    if(pos==x->size())return;
    List.insert(Next(x),vector<char>(x->begin()+pos,x->end()));
    x->erase(x->begin()+pos,x->end());
}
void Update(){
    for(it i=List.begin();i!=List.end();i++){
        while(i->size()>=(block<<1))Split(i,i->size()-block);
        while(Next(i)!=List.end()&&i->size()+Next(i)->size()<=block)Merge(i);
        while(Next(i)!=List.end()&&Next(i)->empty())List.erase(Next(i));
    }
}
void Insert(int pos,const vector<char>&ch){
    it curr=Find(pos);
    if(!List.empty())Split(curr,pos);
    List.insert(Next(curr),ch);
    Update();
}
void Delete(int L,int R){
    it L_block,R_block;
    L_block=Find(L);Split(L_block,L);
    R_block=Find(R);Split(R_block,R);
    R_block++;
    while(Next(L_block)!=R_block)List.erase(Next(L_block));
    Update();
}
int main(){
    vector<char>ch;int len,pos,n;
    cin>>n;
    while(n--){
        char opt[7];cin>>opt;
        if(opt[0]=='M')cin>>pos;
        if(opt[0]=='I'){
            ch.clear();cin>>len;ch.resize(len);
            for(int i=0;i<len;i++){
                ch[i]=getchar();
                while(ch[i]<32||ch[i]>126)ch[i]=getchar();
            }
            Insert(pos,ch);
        }
        if(opt[0]=='D'){cin>>len;Delete(pos,pos+len);}
        if(opt[0]=='G'){cin>>len;Output(pos,pos+len);}
        if(opt[0]=='P')pos--;
        if(opt[0]=='N')pos++;
    }
    return 0;
}
