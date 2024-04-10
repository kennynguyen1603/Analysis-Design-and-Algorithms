
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

// Hàm tính tổng các phần tử trong một vector
int calculateSum(const vector<int> &subset)
{
    int sum = 0;
    for (int num : subset)
    {
        sum += num;
    }
    return sum;
}

// Hàm tìm cách chia tập trọng số thành hai tập con sao cho hiệu tổng là nhỏ nhất (sử dụng vét cạn)
void findMinSubsetDifference(const vector<int> &arr)
{
    int n = arr.size();
    int min_diff_brute_force = INT_MAX;
    vector<int> best_subset1_brute_force, best_subset2_brute_force;

    // Duyệt qua tất cả các tập con của tập trọng số bằng cách sử dụng bit mask
    for (int mask = 0; mask < (1 << n); ++mask)
    {
        vector<int> subset1, subset2;

        // Tạo hai tập con dựa trên mask
        for (int i = 0; i < n; ++i)
        {
            if (mask & (1 << i))
            {
                subset1.push_back(arr[i]);
            }
            else
            {
                subset2.push_back(arr[i]);
            }
        }

        // Tính tổng của hai tập con
        int sum1 = calculateSum(subset1);
        int sum2 = calculateSum(subset2);

        // Tính hiệu tổng của hai tập con
        int diff = abs(sum1 - sum2);

        // Nếu tìm thấy hiệu nhỏ hơn min_diff hiện tại (vét cạn)
        if (diff < min_diff_brute_force)
        {
            min_diff_brute_force = diff;
            best_subset1_brute_force = subset1;
            best_subset2_brute_force = subset2;
        }
    }

    // In ra cách chia tốt nhất từ phương pháp vét cạn
    cout << "Best arrangement from brute force method:\n";
    cout << "First subset: ";
    for (int num : best_subset1_brute_force)
    {
        cout << num << " ";
    }
    cout << "\nSecond subset: ";
    for (int num : best_subset2_brute_force)
    {
        cout << num << " ";
    }
    cout << "\n";
    cout << "The minimum difference from brute force method is: " << min_diff_brute_force << "\n";
}

void findMinRec(vector<int> &arr, vector<bool> &used, int index, int curr_sum, int total_sum)
{
    // Nếu đã xét hết các trọng số trong tập arr
    if (index == arr.size())
    {
        // Tính hiệu giữa tổng của hai tập con
        int diff = abs((total_sum - curr_sum) - curr_sum);

        // Nếu hiệu này nhỏ hơn min_diff hiện tại
        if (diff < min_diff)
        {
            // Cập nhật min_diff và lưu lại cách chia tốt nhất vào best_arrangement
            min_diff = diff;
            best_arrangement = used;
        }
        return;
    }

    // TH1: Chọn trọng số tại index vào tập con thứ nhất
    used[index] = true;
    findMinRec(arr, used, index + 1, curr_sum + arr[index], total_sum);

    // TH2: Không chọn trọng số tại index vào tập con thứ nhất
    used[index] = false;
    findMinRec(arr, used, index + 1, curr_sum, total_sum);
}

// Hàm chính để tìm cách chia tập trọng số thành hai tập con sao cho hiệu tổng là nhỏ nhất
void findMinAndPrintArrangement(vector<int> &arr)
{
    int total_sum = 0;
    for (int num : arr)
    {
        total_sum += num;
    }

    // Gọi hàm backtracking để tìm cách chia tốt nhất
    vector<bool> used(arr.size(), false);
    findMinRec(arr, used, 0, 0, total_sum);

    // In ra cách chia tốt nhất từ phương pháp backtracking
    cout << "Best arrangement from backtracking method:\n";
    printArrangement(arr, best_arrangement);
    cout << "The minimum difference from backtracking method is: " << min_diff << "\n";

    // Gọi hàm vét cạn để so sánh
    findMinSubsetDifference(arr);
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
