#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int maximizeToys(vector<int> prices, int K)
{
    sort(prices.begin(), prices.end());
    int numberOfToys = 0;
    int totalCostUsed = 0;

    for (auto price : prices)
    {
        if (price <= K)
        {
            K -= price;
            totalCostUsed += price;
            numberOfToys++;
        }
    }
    return numberOfToys;
}

int main()
{
    int N, K; // N là số lượng đồ chơi, K là số tiền mà Mark có
    cout << "Nhap so tien ma Mark co: ";
    cin >> K;
    cout << "Nhap so luong do choi cua cua hang: ";
    cin >> N;
    vector<int> prices(N);
    cout << "Nhap gia tien moi mon do choi: ";
    for (int i = 0; i < N; ++i)
    {
        cin >> prices[i];
    }
    cout << "So luong do choi toi da Mark co the mua: " << maximizeToys(prices, K) << endl;
    return 0;
}