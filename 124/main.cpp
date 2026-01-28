#include <iostream>
#include <climits>
#include <algorithm>
#include <queue>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

int maxPathSum(TreeNode *root)
{
    int res = INT_MIN;
    auto post_order_dfs = [&](this auto &&post_order_dfs, TreeNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int left_val = post_order_dfs(node->left);
        int right_val = post_order_dfs(node->right);
        int ret_val = node->val + max({left_val, right_val, 0});
        res = max({res, ret_val, left_val + right_val + node->val});
        return ret_val;
    };
    post_order_dfs(root);
    return res;
}

int main()
{
    int num;
    queue<TreeNode *> parent_que;
    TreeNode *dummy_node = new TreeNode();
    bool parent_left = false;
    parent_que.push(dummy_node);
    for (cin >> num; num > 0; num--)
    {
        string val;
        cin >> val;
        TreeNode *cur_input = nullptr;
        if (val != "null")
        {
            cur_input = new TreeNode(stoi(val));
        }

        TreeNode *cur_parent = parent_que.front();
        if (parent_left)
        {
            if (cur_parent != nullptr)
            {
                cur_parent->left = cur_input;
            }
        }
        else
        {
            if (cur_parent != nullptr)
            {
                cur_parent->right = cur_input;
            }
            parent_que.pop();
        }
        parent_left = !parent_left;

        parent_que.push(cur_input);
    }
    cout << maxPathSum(dummy_node->right);
    return 0;
}