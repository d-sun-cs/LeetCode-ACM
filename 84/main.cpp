#include <vector>
#include <iostream>
#include <stack>
using namespace std;

class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int n = heights.size();
        auto h = [&](int i)
        {
            return (i == 0 || i == n + 1) ? 0 : heights[i - 1];
        };
        vector<int> r_ext(n + 2);
        vector<int> l_ext(n + 2);

        int res = 0;
        stack<int> h_idx;
        for (int i = 1; i <= n + 1; i++)
        {
            int cnt = 1;
            while (!h_idx.empty() && h(h_idx.top()) > h(i))
            {
                int idx = h_idx.top();
                h_idx.pop();
                cnt += l_ext[idx];
                r_ext[idx] = i - idx;
                res = max(res, (r_ext[idx] + l_ext[idx] - 1) * h(idx));
            }
            l_ext[i] = cnt;
            h_idx.push(i);
        }
        return res;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> heights(n);
    for (int i = 0; i < n; i++)
    {
        cin >> heights[i];
    }
    cout << Solution().largestRectangleArea(heights);
    return 0;
}