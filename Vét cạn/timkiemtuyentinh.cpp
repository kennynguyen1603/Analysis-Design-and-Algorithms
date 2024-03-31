#include <iostream>
using namespace std;

int linearSearch(int n, int arr[], int x)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    // int n;
    // cout << "Enter number of array: ";
    // cin >> n;
    int arr[] = {1, 5, 12, -10, 5, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = -1;
    int result = linearSearch(n, arr, x);
    if (result == -1)
    {
        cout << "KHONG TIM THAY";
    }
    else
    {
        cout << result;
    }
    return 0;
}