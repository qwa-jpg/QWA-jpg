// =====================================================================
// CSP 201604 T3 路径解析（路径正规化）
// 思路：按 / 切分 + 栈模拟
//   · 空串 / 相对路径：先拼到当前目录前面，统一成绝对路径
//   · 遍历字符，遇到 / 结算当前段：
//       ".."  -> 栈非空则弹栈（根目录的上一级是它本身，即不弹）
//       "."   -> 忽略
//       其他  -> 入栈
//   · 最后栈中从根到叶依次拼接，空栈即根目录 "/"
// 陷阱：输入路径可能是空串（getline 要能读到空行）
// =====================================================================
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::getline;
using std::string;
using std::vector;

string solve(const string& cur, string path) {
    if (path.empty() || path[0] != '/')
        path = cur + "/" + path;      // 相对路径（含空串）拼当前目录

    vector<string> st;
    string name;
    path += '/';                      // 哨兵，保证最后一段也能结算
    for (char c : path) {
        if (c == '/') {
            if (name == "..") {
                if (!st.empty()) st.pop_back();
            } else if (!name.empty() && name != ".") {
                st.push_back(name);
            }
            name.clear();
        } else {
            name += c;
        }
    }

    string res = "/";
    for (size_t i = 0; i < st.size(); ++i) {
        if (i) res += '/';
        res += st[i];
    }
    return res;
}

int main() {
    int P;
    cin >> P;
    cin.ignore();                     // 吃掉 P 后面的换行
    string cur;
    getline(cin, cur);

    while (P--) {
        string path;
        getline(cin, path);
        if (!path.empty() && path.back() == '\r') path.pop_back();  // 防 CRLF
        cout << solve(cur, path) << '\n';
    }
    return 0;
}
