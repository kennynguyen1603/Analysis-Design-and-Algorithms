#include <iostream>
#include <vector>

using namespace std;

int knapsack(int W, vector<int> &wt, vector<int> &val, int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(W + 1));

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (wt[i - 1] <= w)
            {
                dp[i][w] = max(val[i] + dp[i - 1][w - wt[i]], dp[i - 1][w]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main()
{
    int n;
    int W;

    cout << "Nhap so luong vat: ";
    cin >> n;
    cout << "Nhap trong luong toi da cua ba lo: ";
    cin >> W;

    vector<int> val(n), wt(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Nhap gia tri va trong luong cho vat " << i + 1 << ": ";
        cin >> val[i] >> wt[i];
    }

    cout << "Gia tri lon nhat co the dat duoc la: " << knapsack(W, wt, val, n) << endl;

    return 0;
}
