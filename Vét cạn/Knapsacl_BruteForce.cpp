#include <iostream>
#include <vector>
using namespace std;

int calculateValue(const vector<int> &w, const vector<int> &v, int W, vector<bool> &selected)
{
    int totalWeight = 0, totalValue = 0;
    for (int i = 0; i < selected.size(); ++i)
    {
        if (selected[i])
        {
            totalWeight += w[i];
            totalValue += v[i];
        }
    }
    return (totalWeight <= W) ? totalValue : 0;
}

int knapsackBruteForce(const vector<int> &w, const vector<int> &v, int W)
{
    int n = w.size();
    int maxValue = 0;
    for (int mask = 0; mask < (1 << n); ++mask)
    {
        vector<bool> selected(n, false);
        for (int i = 0; i < n; ++i)
        {
            if (mask & (1 << i))
            {
                selected[i] = true;
            }
        }
        int currValue = calculateValue(w, v, W, selected);
        if (currValue > maxValue)
        {
            maxValue = currValue;
        }
    }
    return maxValue;
}

int main()
{
    vector<int> weights = {11, 2, 5, 1, 6};
    vector<int> values = {1, 3, 5, 3, 10};
    int W = 10;

    cout << "Giá trị tối đa có thể đạt được là: " << knapsackBruteForce(weights, values, W);
    return 0;
}

// Gốc
// ├─ Không chọn vật phẩm nào (trọng lượng tổng = 0, giá trị tổng = 0)
// ├─ Chọn Vật phẩm 1 (trọng lượng tổng = 1, giá trị tổng = 1)
// ├─ Chọn Vật phẩm 2 (trọng lượng tổng = 2, giá trị tổng = 2)
// ├─ Chọn Vật phẩm 3 (trọng lượng tổng = 3, giá trị tổng = 3)
// ├─ Chọn Vật phẩm 1 và 2 (trọng lượng tổng = 3, giá trị tổng = 3)
// ├─ Chọn Vật phẩm 1 và 3 (trọng lượng tổng = 4, giá trị tổng = 4) [Giải pháp tối ưu cho giới hạn trọng lượng này]
// ├─ Chọn Vật phẩm 2 và 3 (vượt quá trọng lượng giới hạn)
// └─ Chọn tất cả vật phẩm (vượt quá trọng lượng giới hạn)
