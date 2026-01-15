#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
using namespace std;
string minWindow(string s, string t)
{
    int min_delta = s.size();
    int min_idx = -1;
    queue<int> que;
    unordered_map<char, int> s_map;
    unordered_map<char, int> t_map;
    unordered_set<char> ready_cnt;
    for (auto c : t)
    {
        t_map[c]++;
    }
    for (int i = 0; i < s.size(); i++)
    {
        if (t_map.contains(s[i]))
        {
            que.push(i);
            s_map[s[i]]++;
            if (s_map[s[i]] == t_map[s[i]])
            {
                ready_cnt.insert(s[i]);
            }
            while (ready_cnt.size() == t_map.size())
            {
                int cur_delta = i - que.front();
                char left_ch = s[que.front()];
                if (cur_delta < min_delta)
                {
                    min_idx = que.front();
                    min_delta = cur_delta;
                }
                s_map[left_ch]--;
                if (s_map[left_ch] < t_map[left_ch])
                {
                    ready_cnt.erase(left_ch);
                }
                que.pop();
            }
        }
    }
    return min_idx == -1 ? "" : s.substr(min_idx, min_delta + 1);
}

int main()
{
    string s, t;
    cin >> s >> t;
    cout << minWindow(s, t);
    return 0;
}