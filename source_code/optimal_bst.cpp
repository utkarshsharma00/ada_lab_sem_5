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
    //yet to be written 
}
