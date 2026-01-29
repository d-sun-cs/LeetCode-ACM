#include <iostream>
#include <queue>
#include <limits>
#include <format>
using namespace std;

class MedianFinder
{
public:
    priority_queue<int> s;
    priority_queue<int, vector<int>, greater<int>> g;
    MedianFinder()
    {
        s.push(numeric_limits<int>::min());
        g.push(numeric_limits<int>::max());
    }

    void addNum(int num)
    {
        if (num > g.top()) {
            g.push(num);
        } else {
            s.push(num);
        }
        if (s.size() == g.size() + 2)
        {
            int move = s.top();
            s.pop();
            g.push(move);
        } else if (g.size() == s.size() + 1){
            int move = g.top();
            g.pop();
            s.push(move);
        }
    }

    double findMedian()
    {
        if (s.size() == g.size()) {
            return (s.top() + g.top()) / 2.0;
        } else {
            return s.top();
        }
    }
};

int main()
{
    // 测试用例说明（针对 Problem 295: 数据流的中位数）
    // 格式示例：
    // 第一行：q（操作数量）
    // 接下来 q 行，每行以一个整数表示操作类型：
    //   1 x    表示执行 addNum(x)
    //   2      表示执行 findMedian()，此时程序应输出当前中位数（以浮点数形式输出，保留至少1位小数）
    // 示例：
    // 5
    // 1 1
    // 1 2
    // 2
    // 1 3
    // 2
    // 对应期望输出：
    // 1.5
    // 2.0
    // 请在这里实现你的解法，测试系统会按本注释中的格式为程序提供输入。
    int q;
    cin >> q;
    MedianFinder mf;
    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int num;
            cin >> num;
            mf.addNum(num);
        } else if (op == 2) {
            cout << format("{:.1f}", mf.findMedian()) << endl;
        }
    }
    return 0;
}