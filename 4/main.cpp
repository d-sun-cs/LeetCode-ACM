#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
#include <format>
using namespace std;

class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        if (nums1.size() > nums2.size())
        {
            swap(nums1, nums2);
        }
        int m = nums1.size();
        int n = nums2.size();
        // 为了处理边界，需要加最值哨兵
        // 为了正常二分索引，最好不引入负数（-1）索引
        auto vals1 = [&](int idx)
        {
            return idx <= 0 ? INT_MIN : (idx > m ? INT_MAX : nums1[idx - 1]);
        };
        auto vals2 = [&](int idx)
        {
            return idx <= 0 ? INT_MIN : (idx > n ? INT_MAX : nums2[idx - 1]);
        };
        // 默认左闭右开
        int left = 0;
        int right = m + 1;
        while (left < right)
        {
            int i = (left + right) / 2;
            int j = (m + n + 1) / 2 - i;
            if (vals1(i + 1) > vals2(j))
            {
                right = i;
            }
            else
            {
                left = i + 1;
            }
        }
        int j = (m + n + 1) / 2 - left;
        int max1 = max(vals1(left), vals2(j));
        int min2 = min(vals1(left + 1), vals2(j + 1));
        return (m + n) % 2 == 0 ? (max1 + min2) / 2.0 : max1;
    }
};

int main()
{
    int m, n;
    cin >> m;
    vector<int> nums1(m);
    for (int i = 0; i < m; i++)
    {
        cin >> nums1[i];
    }
    cin >> n;
    vector<int> nums2(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums2[i];
    }
    cout << format("{:.5f}", Solution().findMedianSortedArrays(nums1, nums2));
    return 0;
}