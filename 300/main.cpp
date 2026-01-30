#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        auto end = nums.begin();
        for (auto num : nums)
        {
            auto it = lower_bound(nums.begin(), end, num);
            if (it == end)
            {
                end++;
            }
            *it = num;
        }
        return end - nums.begin();
    }
};
int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (auto& num: nums) {
        cin >> num;
    }
    cout << Solution().lengthOfLIS(nums);
    return 0;
}
