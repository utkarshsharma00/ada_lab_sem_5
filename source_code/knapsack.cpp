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

void unbounded_knapsack(vector<int> &weight, vector<int> &prices, int Capacity)
{
    vector<int> strg(Capacity + 1);
    for (int i = 1; i <= Capacity; i++)
    {
        for (int j = 1; j < weight.size(); j++)
        {
            if (i >= weight[j])
            {
                strg[i] = max(strg[i - weight[j]] + prices[j], strg[i]);
            }
        }
    }

    cout << strg[Capacity] << endl;
}

int main(int argc, char **argv)
{
    vector<int> weight{2, 5, 1, 3, 4};
    vector<int> prices{15, 14, 10, 45, 30};
    knapsack(weight, prices, 7);
    unbounded_knapsack(weight, prices, 7);
}
