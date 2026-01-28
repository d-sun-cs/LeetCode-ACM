#include <vector>
#include <string>
#include <iostream>
using namespace std;


vector<vector<string>> solveNQueens(int n)
{
    vector<bool> col_occ(n);
    vector<bool> lr_diag_occ(2 * n - 1);
    vector<bool> rl_diag_occ(2 * n - 1);
    vector<vector<string>> res;
    vector<string> tmp;
    auto dfs = [&](this auto &&dfs, int row)
    {
        if (row == n)
        {
            res.emplace_back(tmp);
            return;
        }
        string inter_pos;
        for (int col = 0; col < n; col++)
        {
            if (col_occ[col] || lr_diag_occ[row + n - 1 - col] || rl_diag_occ[row + col])
            {
                inter_pos.push_back('.');
                continue;
            }
            col_occ[col] = true;
            lr_diag_occ[row + n - 1 - col] = true;
            rl_diag_occ[row + col] = true;
            inter_pos.push_back('Q');
            inter_pos.append(n - 1 - col, '.');
            tmp.emplace_back(inter_pos);
            dfs(row + 1);
            col_occ[col] = false;
            lr_diag_occ[row + n - 1 - col] = false;
            rl_diag_occ[row + col] = false;
            inter_pos.erase(col);
            inter_pos.push_back('.');
            tmp.pop_back();
        }
    };
    dfs(0);
    return res;
}
int main()
{
    int n;
    cin >> n;
    vector<vector<string>> res = solveNQueens(n);
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < n; j++) {
            cout << res[i][j] << endl;
        }
        cout << endl;
    }
    return 0;
}