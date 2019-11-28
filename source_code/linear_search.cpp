#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    int arr[] = {50, 60, 70, 90, 2, 33, -14, 61};
    int find;
    cin >> find;

    for (int index = 0; index < 8; index++)
    {
        if (find == arr[index])
        {
            cout << "The element is present at index = "<<index;
            return 0;
        }
    }
    cout <<"The element does not exist in the array "<< -1;
}
