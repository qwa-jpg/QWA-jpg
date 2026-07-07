stack
push(x) – 入栈
pop() – 出栈（不返回值）
top() – 访问栈顶元素
empty() – 判空
size() – 元素个数
注意事项：没有迭代器，不能遍历；pop() 只是删除，不返回元素。
queue
push(x) – 入队（尾部）
pop() – 出队（头部）
front() – 访问队首元素
back() – 访问队尾元素
empty(), size() – 判空、大小
注意事项：没有迭代器，不可遍历；不能像 stack 一样用 top，而是 front / back。

list(双向链表)
push_back(x), push_front(x) – 尾部/头部插入
pop_back(), pop_front() – 尾部/头部删除
insert(pos, x) – 在迭代器位置前插入
erase(pos) – 删除迭代器所指元素
size(), empty(), clear()
特殊操作：splice, remove, remove_if, unique, merge, sort, reverse
注意：不支持随机访问（无 [] 和 at），迭代器不能 +n，只能 ++/--。
for (auto it = lt.begin(); it != lt.end(); ++it)迭代器

priority_queue（优先队列 / 堆）
默认大顶堆
push(x) – 插入并调整堆
pop() – 删除堆顶（最大值）
top() – 返回堆顶（不删除）
empty(), size()
自定义排序：priority_queue<int, vector<int>, greater<int>> 变为小顶堆；也可传入自定义比较函数对象。
无迭代器，不可遍历。

