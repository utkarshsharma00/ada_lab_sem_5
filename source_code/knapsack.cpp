#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <climits>
using namespace std;

void knapsack(vector<int> &weight, vector<int> &prices, int Capacity)
{
    vector<vector<int>> strg(weight.size() + 1, vector<int>(Capacity + 1, false));

    for (int i = 1; i < strg.size(); i++)
    {
        for (int j = 1; j < strg[0].size(); j++)
        {

            if (j >= weight[i - 1] && strg[i - 1][j - weight[i - 1]] + prices[i - 1] >= strg[i - 1][j])
            {
                strg[i][j] = strg[i - 1][j - weight[i - 1]] + prices[i - 1];
            }
            else
            {
                strg[i][j] = strg[i - 1][j];
            }
        }
    }

    cout << strg[strg.size() - 1][strg[0].size() - 1] << endl;
}
