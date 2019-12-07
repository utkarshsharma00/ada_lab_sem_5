#include <iostream> //string1 is mapped Horizontally and string2 is mapped Vertically as per me and this leads to transpose of the actual matrix in my notes
#include <vector>
#include <bits/stdc++.h>
#include <climits>

using namespace std;

void LCS(string s1, string s2)
{
    vector<vector<int>> storage(s1.length() + 1, vector<int>(s2.length() + 1));
    for (int i = storage.size() - 1; i >= 0; i--)
    {
        for (int j = storage[0].size() - 1; j >= 0; j--)

            if (j == storage[0].size() - 1)
            {
                storage[i][j] = 0;
            }

            else if (i == storage.size() - 1)
            {
                storage[i][j] = 0;
            }

            else
            {
                if (s1[i] == s2[j])
                {
                    storage[i][j] = 1 + storage[i + 1][j + 1];
                }
                else
                {
                    storage[i][j] = max(storage[i + 1][j], storage[i][j + 1]);
                }
            }
    }

    for (int i = 0; i < storage.size(); i++)
    {
        for (int j = 0; j < storage[0].size(); j++)
        {
            cout << storage[i][j] << " ";
        }

        cout << endl;
    }
}

int main(int argc, char **argv)
{
    LCS("abcd", "aebd");
}
