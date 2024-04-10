#include <iostream>
#include <vector>
using namespace std;

int maxValue = 0; // Giá trị tối đa

void knapsack(int W, vector<int> &w, vector<int> &v, int i, int currWeight, int currValue)
{
    if (i == w.size())
    {
        if (currWeight <= W && currValue > maxValue)
        {
            maxValue = currValue;
        }
        return;
    }

    knapsack(W, w, v, i + 1, currWeight, currValue);

    if (currWeight + w[i] <= W)
    {
        knapsack(W, w, v, i + 1, currWeight + w[i], currValue + v[i]);
    }
}

int main()
{
    vector<int> weights = {11, 2, 5, 1, 6};
    vector<int> values = {1, 3, 5, 3, 10};
    int W = 10;

    knapsack(W, weights, values, 0, 0, 0);
    cout << "Giá trị tối đa có thể đạt được là: " << maxValue;
    return 0;
}

// Gốc (không chọn vật phẩm nào, trọng lượng tổng = 0, giá trị tổng = 0)
// ├─ Chọn Vật phẩm 1 (trọng lượng tổng = 1, giá trị tổng = 1)
// │  ├─ Chọn Vật phẩm 2 (trọng lượng tổng = 3, giá trị tổng = 3)
// │  │  ├─ Chọn Vật phẩm 3 (vượt quá trọng lượng, không thêm)
// │  │  └─ Không chọn Vật phẩm 3 (trọng lượng tổng = 3, giá trị tổng = 3)
// │  └─ Không chọn Vật phẩm 2
// │     ├─ Chọn Vật phẩm 3 (trọng lượng tổng = 4, giá trị tổng = 4)
// │     └─ Không chọn Vật phẩm 3 (trọng lượng tổng = 1, giá trị tổng = 1)
// └─ Không chọn Vật phẩm 1
//    ├─ Chọn Vật phẩm 2 (trọng lượng tổng = 2, giá trị tổng = 2)
//    │  ├─ Chọn Vật phẩm 3 (vượt quá trọng lượng, không thêm)
//    │  └─ Không chọn Vật phẩm 3 (trọng lượng tổng = 2, giá trị tổng = 2)
//    └─ Không chọn Vật phẩm 2
//       ├─ Chọn Vật phẩm 3 (trọng lượng tổng = 3, giá trị tổng = 3)
//       └─ Không chọn Vật phẩm 3 (trọng lượng tổng = 0, giá trị tổng = 0)
