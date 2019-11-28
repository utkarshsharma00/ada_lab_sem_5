#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <climits>
using namespace std;

int rod_cutting(vector<int> &weight)
{
    vector<int> strg(weight.size(), false);
    strg[0] = 0;
    for (int i = 1; i < strg.size(); i++)
    {
        strg[i] = weight[i];
        int left = 1;
        int right = i - 1;

        while (left <= right)
        {
            if (strg[left] + strg[right] >= strg[i])
            {
                strg[i] = strg[left] + strg[right];
            }

            left++;
            right--;
        }
    }

    for (int i = 0; i < strg.size(); i++)
    {
        cout << strg[i] << " ";
    }

    //return strg[strg.size() - 1];
}

int main(int argc, char **argv)
{
    vector<int> weight{0, 3, 5, 6, 15, 10, 25, 12, 24};
    rod_cutting(weight);
}
