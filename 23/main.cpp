#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
};

ListNode *mergeKLists(vector<ListNode *> &lists)
{
    priority_queue<pair<int, ListNode *>, vector<pair<int, ListNode *>>,
                   greater<pair<int, ListNode *>>>
        que;
    for (auto head : lists)
    {
        if (head)
        {

            que.emplace(head->val, head);
        }
    }
    ListNode *dumhead = new ListNode();
    ListNode *curptr = dumhead;
    while (!que.empty())
    {
        auto [minval, minptr] = que.top();
        que.pop();
        curptr->next = minptr;
        curptr = minptr;
        if (curptr->next)
        {
            que.emplace(curptr->next->val, curptr->next);
        }
    }
    return dumhead->next;
}

int main()
{
    // int cases;
    // cin >> cases;
    // while (cases)
    // {
    int k;
    cin >> k;
    vector<ListNode *> lists(k);
    for (int i = 0; i < k; i++)
    {
        int len;
        cin >> len;
        ListNode *dumhead = new ListNode();
        ListNode *curptr = dumhead;
        while (len)
        {
            ListNode *visited_val = new ListNode();
            cin >> visited_val->val;
            curptr->next = visited_val;
            curptr = curptr->next;
            len--;
        }
        lists[i] = dumhead->next;
    }
    ListNode *result = mergeKLists(lists);
    // cout << '[';
    while (result)
    {
        cout << result->val;
        if (result->next)
        {
            cout << ' ';
        }
        result = result->next;
    }
    // cout << ']' << endl;
    // cases--;
    // }
}