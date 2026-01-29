#include <iostream>
#include <stack>
using namespace std;
class Solution
{
public:
    int longestValidParentheses(string s)
    {
        stack<pair<char, int>> brkt_len;
        int res = 0;
        brkt_len.emplace('.', 0);
        for (char brkt : s)
        {
            if (brkt == '(')
            {
                brkt_len.emplace(brkt, 0);
            }
            else if (brkt_len.top().first == '(')
            {
                int kept_len = brkt_len.top().second;
                brkt_len.pop();
                brkt_len.top().second += kept_len + 2;
                res = max(res, brkt_len.top().second);
            } else {
                brkt_len.emplace(brkt, 0);
            }
        }
        return res;
    }
};
int main()
{
    string input;
    cin >> input;
    cout << Solution().longestValidParentheses(input);
    return 0;
}
