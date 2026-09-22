// =====================================================================
// CCF CSP 201912-3 化学方程式
// 题意：给 n 个化学方程式（长度 <= 1000），判断是否配平：
//       等号两边每种元素的原子个数完全相同 -> Y，否则 N
//
// 文法（按题目 BNF 简化）：
//   equation ::= expr '=' expr
//   expr     ::= coef formula ('+' coef formula)*
//   formula  ::= term+                    （项直接相连，如 H2O、(OH)2）
//   term     ::= element coef | '(' formula ')' coef
//   element  ::= 大写字母 [小写字母]       （如 H、O、Ca）
//   coef     ::= 数字串 | 空串（空串按系数 1 处理）
//
// 思路：递归下降解析，从左到右扫描字符串：
//   · 大写字母 -> 读元素（可能带一个小写字母），再读下标数字，乘系数计入 map
//   · '('      -> 递归解析括号内部（遇 ')' 停止），读括号后的系数，
//                 把内部计数 x 括号系数 x 外层系数 合并进 map
//   · '+' '=' ')' -> 当前化学式 / 表达式结束
// 等号两侧各自得到 map<元素, 原子个数>，两个 map 相等即配平。
// 括号嵌套深度 <= 500（长度 <= 1000），递归完全安全。
// 复杂度 O(总字符数)，n <= 100，轻松通过。
// =====================================================================
#include <bits/stdc++.h>
using namespace std;

string s;
int pos, len;

// 读系数：当前位置是数字则读完整数；否则返回 -1 表示空串（系数按 1 处理）

int parseNum() {
    if (pos >= len || !isdigit(s[pos])) return -1;
    int num = 0;
    while (pos < len && isdigit(s[pos]))
        num = num * 10 + s[pos++] - '0';
    return num;
}
// 解析化学式：所有元素计数乘 mult 累加进 mp
// 遇到 ')'、'+'、'=' 或字符串末尾时停止
void parseFormula(map<string, int>& mp, int mult) {
    while (pos < len && s[pos] != ')' && s[pos] != '+' && s[pos] != '=') {
        if (isupper(s[pos])) {                      // 元素
            string el(1, s[pos++]);
            if (pos < len && islower(s[pos])) el += s[pos++];
            int cnt = parseNum();                   // 下标数字
            if (cnt == -1) cnt = 1;
            mp[el] += mult * cnt;
        } else {                                    // '(' 括号项
            pos++;
            map<string, int> tmp;
            parseFormula(tmp, 1);                   // 递归解析括号内部
            pos++;                                  // 跳过 ')'
            int cnt = parseNum();                   // 括号后的系数
            if (cnt == -1) cnt = 1;
            for (auto& p : tmp)
                mp[p.first] += mult * cnt * p.second;
        }
    }
}

// 解析等号一侧的表达式：coef formula ('+' coef formula)*
void parseExpr(map<string, int>& mp) {
    int coef = parseNum();
    if (coef == -1) coef = 1;
    parseFormula(mp, coef);
    while (pos < len && s[pos] == '+') {
        pos++;
        coef = parseNum();
        if (coef == -1) coef = 1;
        parseFormula(mp, coef);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        cin >> s;
        len = (int)s.size();
        pos = 0;
        map<string, int> L, R;
        parseExpr(L);      // 解析到 '=' 自动停止
        pos++;             // 跳过 '='
        parseExpr(R);
        puts(L == R ? "Y" : "N");   // map 相等 <=> 元素种类与个数都相同
    }
    return 0;
}
