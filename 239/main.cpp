#include <bits/stdc++.h>


using namespace std;
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> res;
    deque<int> deq;
    for (int i = 0; i < nums.size(); i++) {
        while (!deq.empty() && nums[deq.back()] <= nums[i]) {
            deq.pop_back();
        }
        deq.push_back(i);
        int left = i - k + 1; // inclusive
        if (deq.front() < left) {
            deq.pop_front();
        }
        if (left >= 0) {
            res.push_back(nums[deq.front()]);
        }
    }
    return res;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    vector<int> res = maxSlidingWindow(nums, k);
    for (int i = 0; i < n - k + 1; i++)
    {
        cout << res[i] << ' ';
    }
}