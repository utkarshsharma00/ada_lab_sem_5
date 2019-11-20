#include <iostream> //see this code for errors
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

void optimal_bst(vector<int> &elements, vector<int> &frequency)
{
    vector<int> sum_of_frequency(frequency.size(), 0);
    sum_of_frequency[0] = frequency[0];
    for (int i = 0; i < frequency.size(); i++)
    {
        sum_of_frequency[i] = sum_of_frequency[i - 1] + frequency[i];
    }
    
    vector<vector<int>> tabulation(elements.size(), vector<int>(elements.size(), 0)); //tabulation is essentially storage
    int mymin = INT_MAX;
    for (int gap = 0; gap < tabulation.size(); gap++)
    {
        for (int i = 0, j = i + gap; j < tabulation.size(); i++, j++)
        {
            if (gap == 0)
            {
                tabulation[i][j] = frequency[i];
            }

            else if (gap == 1)
            {
                tabulation[i][j] = min(2 * tabulation[i][j - 1] + tabulation[i + 1][j],
                                       tabulation[i][j - 1] + 2 * tabulation[i + 1][j]);
            }

            else
            {
                int mymin = INT_MAX;
                for (int k = -1; k < gap; k++)
                {
                    int lhs = k == -1 ? 0 : tabulation[i][j - gap + k];
                    int rhs = k == gap - 1 ? 0 : tabulation[i + 2 + k][j];

                    int total_cost = lhs + rhs + sum_of_frequency[j];

                    if (i > 0)
                    {
                        total_cost -= sum_of_frequency[i - 1];
                    }

                    mymin = min(mymin, total_cost);
                }

                tabulation[i][j] = mymin;
            }
        }
    }

    for (int i = 0; i < tabulation.size(); i++)
    {
        for (int j = 0; j < tabulation[0].size(); j++)
        {
            cout << tabulation[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char **argv)
{
    vector<int> elements = {5, 7, 8, 17, 20};
    vector<int> frequency = {4, 7, 5, 1, 2};

    optimal_bst(elements, frequency);
}
