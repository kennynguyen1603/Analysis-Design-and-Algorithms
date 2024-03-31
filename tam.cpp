#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maximize_toys(vector<int> &prices, int K)
{

    sort(prices.begin(), prices.end());

    int count_toys = 0;
    int total_cost = 0;

    for (int i = 0; i < prices.size(); ++i)
    {
        if (total_cost + prices[i] <= K)
        {
            total_cost += prices[i];
            count_toys++;
        }
        else
        {
            // Nếu tổng chi phí vượt quá số tiền K, dừng lại vì không thể mua thêm đồ chơi nào nữa
            break;
        }
    }

    return count_toys;
}

int main()
{
    int N, K; // Số lượng đồ chơi và số tiền Mark có
    cout << "Nhập số lượng đồ chơi: ";
    cin >> N;
    cout << "Nhập số tiền Mark có: ";
    cin >> K;

    vector<int> prices(N);
    cout << "Nhập giá của từng đồ chơi:" << endl;
    for (int i = 0; i < N; ++i)
    {
        cin >> prices[i];
    }

    int max_toys = maximize_toys(prices, K);

    cout << "Mark có thể mua tối đa " << max_toys << " đồ chơi." << endl;

    return 0;
}