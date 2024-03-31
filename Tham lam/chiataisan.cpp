#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <climits>
using namespace std;

void findMinDifference(const vector<int> &values)
{
    int totalSum = accumulate(values.begin(), values.end(), 0);
    int n = values.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(totalSum / 2 + 1, false));
    for (int i = 0; i <= n; ++i)
    {
        dp[i][0] = true;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= totalSum / 2; ++j)
        {
            if (j >= values[i - 1])
            {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - values[i - 1]];
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    int minDiff = INT16_MAX;
    for (int j = totalSum / 2; j >= 0; --j)
    {
        if (dp[n][j])
        {
            minDiff = totalSum - 2 * j;
            break;
        }
    }
    cout << "Chenh lech tong gia tri it nhat la: " << minDiff << endl;
}

int main()
{
    int N;
    cout << "Nhap so luong do vat N (<10): ";
    cin >> N;

    vector<int> values(N);
    cout << "Nhap gia tri tung do vat:" << endl;
    for (int i = 0; i < N; ++i)
    {
        cin >> values[i];
    }

    findMinDifference(values);

    return 0;
}
