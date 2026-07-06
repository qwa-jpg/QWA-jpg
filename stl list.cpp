#include <list>
using namespace std;
初始化
list<int> l1;                    // 空链表
list<int> l2(5, 10);             // {10, 10, 10, 10, 10}
list<int> l3 = {1, 2, 3, 4};     // C++11列表初始化
list<int> l4(l3.begin(), l3.end());// 迭代器区间拷贝
list<int> l5(move(l3));          // 移动构造（l3变空）




插入
list<int> lst = {1, 2, 3};
lst.push_front(0);               // 头插 {0,1,2,3}
lst.push_back(4);                // 尾插 {0,1,2,3,4}
auto it = find(lst.begin(), lst.end(), 2);
if (it != lst.end()) {
    lst.insert(it, 99);          // 在2之前插入99（O(1)）
    lst.emplace(it, 88);         // 原地构造，性能更优
}




关于emplace的用法
struct Student {
    string name;
    int age;
    Student(string n, int a) : name(n), age(a) { 
        cout << "构造" << endl; 
    }
};
list<Student> lst;
lst.push_back(Student("张三", 18)); 
lst.emplace_back("张三", 18); 
//这里emplace_back用的是插入最后





删除
lst.pop_front();                 // 删除头
lst.pop_back();                  // 删除尾
auto it = find(lst.begin(), lst.end(), 3);
if (it != lst.end()) lst.erase(it); // 删除指定迭代器位置
lst.remove(99);                  // 删除所有值为99的元素（O(n)）
lst.remove_if([](int n){ return n % 2 == 0; }); // 删除所有偶数
lst.unique();                    // 删除**连续**重复元素（保留一个）






遍历
// 正向遍历（范围for）
for (int val : lst) cout << val << " ";
实例
int 目标值 = 5;
for (int val : lst) {
    if (val == 目标值) {  // 这里的 val 才是被拿来和目标对比的
        cout << "找到了！";
    }
}
// 正向迭代器
for (auto it = lst.begin(); it != lst.end(); ++it) cout << *it << " ";
// 反向遍历（rbegin/rend）
for (auto it = lst.rbegin(); it != lst.rend(); ++it) cout << *it << " ";





查找
#include <algorithm>
auto it = find(lst.begin(), lst.end(), 5); // O(n)线性查找
if (it != lst.end()) {
    cout << "Found: " << *it;
} else {
    cout << "Not found";
}
// 性能提示：频繁查找应改用 std::set 或 unordered_set







内存释放
// 场景1：清空元素（size变为0，但底层节点内存不一定立即归还OS）
lst.clear();
// 场景2：真正释放内存块（将list与空list交换）
list<int>().swap(lst);   // 或 lst = {};
// 场景3：离开作用域自动析构（最常用）
{ list<int> tmp = {1,2,3}; } // 出花括号自动释放所有节点
int main() {
    cout << "① 主函数开始" << endl;
    // ========== 关键：大括号作用域 ==========
    {
        cout << "② 进入内部花括号 { " << endl;
        
        list<Item> tmp;                    // 栈上创建 tmp（空的）
        tmp.emplace_back(10);              // 堆上造节点 10
        tmp.emplace_back(20);              // 堆上造节点 20
        tmp.emplace_back(30);              // 堆上造节点 30
        
        cout << "③ 当前 list 大小为: " << tmp.size() << endl;
        cout << "④ 准备离开内部花括号 } " << endl;
        
    } // <--- ！！！右花括号就在这里生效！！！
    // 执行到这一行时，tmp 的析构函数被自动调用，
    // 因此上面 10,20,30 的 ~Item() 会在此刻依次打印。
    
    cout << "⑤ 已经离开内部花括号" << endl;
    cout << "⑥ 此时 tmp 已不存在，下面那行代码如果取消注释，编译直接报错" << endl;
    // cout << tmp.size(); // 取消注释会编译错误：'tmp' was not declared

    cout << "⑦ 主函数结束" << endl;
    return 0;
}
