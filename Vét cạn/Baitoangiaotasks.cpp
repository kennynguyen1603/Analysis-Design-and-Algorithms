#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double standardDeviation(const vector<int> &values)
{
    double mean = 0.0;
    int sum = 0;
    for (int value : values)
    {
        sum += value;
    }
    mean = static_cast<double>(sum) / values.size();

    double standardDev = 0.0;
    for (int value : values)
    {
        standardDev += pow(value - mean, 2);
    }
    return sqrt(standardDev / (values.size() - 1));
}

int main()
{
    int n, m;
    cout << "Nhap so luong cong viec (n) va so luong cong nhan (m): ";
    cin >> n >> m;
    vector<int> wages(n);

    cout << "Nhap thu lao cho moi cong viec: ";
    for (int &wage : wages)
    {
        cin >> wage;
    }

    sort(wages.begin(), wages.end(), greater<int>());

    vector<int> totalWages(m, 0);

    for (int wage : wages)
    {
        auto minIt = min_element(totalWages.begin(), totalWages.end());
        *minIt += wage;
    }

    for (int i = 0; i < m; ++i)
    {
        cout << "Tong thu lao cong nhan " << i + 1 << ": " << totalWages[i] << endl;
    }

    double deviation = standardDeviation(totalWages);
    cout << "Do lech chuan: " << deviation << endl;

    return 0;
}
