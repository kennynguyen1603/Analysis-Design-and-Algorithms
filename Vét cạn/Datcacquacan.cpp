
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;
int min_diff = INT_MAX;
vector<bool> best_arrangement;

void printArrangement(const vector<int> &arr, const vector<bool> &used)
{
    cout << "First subset: ";
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (used[i])
        {
            cout << arr[i] << " ";
        }
    }
    cout << "\nSecond subset: ";
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (!used[i])
        {
            cout << arr[i] << " ";
        }
    }
    cout << "\n";
}

void findMinRec(vector<int> &arr, vector<bool> &used, int index, int curr_sum, int total_sum)
{
    if (index == arr.size())
    {
        int diff = abs((total_sum - curr_sum) - curr_sum);
        if (diff < min_diff)
        {
            min_diff = diff;
            best_arrangement = used;
        }
        return;
    }

    used[index] = true;
    findMinRec(arr, used, index + 1, curr_sum + arr[index], total_sum);

    used[index] = false;
    findMinRec(arr, used, index + 1, curr_sum, total_sum);
}

void findMinAndPrintArrangement(vector<int> &arr)
{
    int total_sum = 0;
    for (int num : arr)
    {
        total_sum += num;
    }

    vector<bool> used(arr.size(), false);
    findMinRec(arr, used, 0, 0, total_sum);

    printArrangement(arr, best_arrangement);
    cout << "The minimum difference is: " << min_diff << "\n";
}

int main()
{
    int n;
    cout << "Enter the number of weights: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the weights: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    findMinAndPrintArrangement(arr);
    return 0;
}
