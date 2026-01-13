#include <vector>
#include <stack>
#include <utility>
#include <iostream>

using namespace std;

int trap(vector<int> &height)
{
    stack<pair<int, int>> stk;
    int res = 0;
    for (int i = 0; i < height.size(); i++)
    {
        if (stk.empty() || stk.top().first >= height[i])
        {
            stk.emplace(height[i], i);
        }
        else
        {
            int lastH = -1;
            while (!stk.empty() && stk.top().first <= height[i])
            {
                int deltaH = stk.top().first - lastH;
                int deltaW = i - stk.top().second - 1;
                res += deltaH * deltaW;
                lastH = stk.top().first;
                stk.pop();
            }
            if (!stk.empty())
            {
                int deltaH = height[i] - lastH;
                int deltaW = i - stk.top().second - 1;
                res += deltaH * deltaW;
            }
            stk.emplace(height[i], i);
        }
    }
    return res;
}

int main()
{
    int n;
    // while (cin >> n)
    // {
    cin >> n;
    vector<int> input(n);
    for (int i = 0; i < n; i++)
    {
        cin >> input[i];
    }
    cout << trap(input) << endl;
    // }

    return 0;
}