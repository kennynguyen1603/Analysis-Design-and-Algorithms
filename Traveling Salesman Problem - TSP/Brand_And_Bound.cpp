#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Tính khoảng cách giữa hai thành phố
int distance(pair<int, int> &city1, pair<int, int> &city2)
{
    int dx = city1.first - city2.first;
    int dy = city1.second - city2.second;
    return round(sqrt(dx * dx + dy * dy));
}

// Hàm đệ quy để thử tất cả các hoán vị của các thành phố
int tsp_brute_force(vector<pair<int, int>> &cities, vector<int> &path, vector<bool> &visited, int current_length, int current_city)
{
    if (count(visited.begin(), visited.end(), false) == 0)
    {                                                                      // Nếu đã thăm tất cả các thành phố
        return current_length + distance(cities[current_city], cities[0]); // Trở về thành phố ban đầu
    }

    int min_length = INF;
    for (int next_city = 0; next_city < cities.size(); ++next_city)
    {
        if (!visited[next_city])
        {
            visited[next_city] = true;
            path.push_back(next_city);
            int new_length = tsp_brute_force(cities, path, visited, current_length + distance(cities[current_city], cities[next_city]), next_city);
            min_length = min(min_length, new_length);
            path.pop_back();
            visited[next_city] = false;
        }
    }

    return min_length;
}

int main()
{
    // Số lượng thành phố
    int n;
    cout << "Nhap so luong thanh pho: ";
    cin >> n;

    // Nhập tọa độ các thành phố
    vector<pair<int, int>> cities(n);
    cout << "Nhap toa do cac thanh pho:\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Thanh pho " << i + 1 << ": ";
        cin >> cities[i].first >> cities[i].second;
    }

    // Tạo một mảng để lưu đường đi tạm thời
    vector<int> path;
    // Tạo một mảng để theo dõi xem mỗi thành phố đã được thăm chưa
    vector<bool> visited(n, false);
    // Bắt đầu từ thành phố 0
    path.push_back(0);
    visited[0] = true;

    // Tìm độ dài của đường đi tối ưu nhất
    int optimal_length = tsp_brute_force(cities, path, visited, 0, 0);

    cout << "Do dai duong di toi uu: " << optimal_length << endl;
    cout << "Chu trinh toi uu: ";
    for (int city : path)
    {
        cout << city << " ";
    }
    cout << "0\n"; // Quay về thành phố ban đầu

    return 0;
}
