#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <filesystem>
#include <string>

using namespace std;
namespace fs = std::filesystem; // Đặt bí danh cho không gian tên filesystem

const int INF = numeric_limits<int>::max();

class TravelingSalesman
{
private:
    vector<pair<int, int>> cities;

    int distance(const pair<int, int> &city1, const pair<int, int> &city2)
    {
        int dx = city1.first - city2.first;
        int dy = city1.second - city2.second;
        return round(sqrt(dx * dx + dy * dy));
    }

public:
    TravelingSalesman() {}

    bool loadCitiesFromFile(const string &fileName)
    {
        ifstream file(fileName);
        if (!file.is_open())
            return false;

        cities.clear(); // Xóa các thành phố cũ trước khi đọc mới
        int x, y;
        while (file >> x >> y)
        {
            cities.push_back({x, y});
        }
        file.close();
        return true;
    }

    int BruteForce(vector<int> &path)
    {
        if (cities.empty())
            return -1; // Trả về lỗi nếu không có thành phố nào

        vector<bool> visited(cities.size(), false);
        path.clear(); // Xóa path cũ
        path.push_back(0);
        visited[0] = true;
        return tspBruteForce(path, visited, 0, 0);
    }

private:
    int tspBruteForce(vector<int> &path, vector<bool> &visited, int currentLength, int currentCity)
    {
        if (count(visited.begin(), visited.end(), false) == 0)
        {
            return currentLength + distance(cities[currentCity], cities[0]);
        }

        int minLength = INF;
        for (int nextCity = 0; nextCity < cities.size(); ++nextCity)
        {
            if (!visited[nextCity])
            {
                visited[nextCity] = true;
                path.push_back(nextCity);
                int newLength = tspBruteForce(path, visited, currentLength + distance(cities[currentCity], cities[nextCity]), nextCity);
                minLength = min(minLength, newLength);
                path.pop_back();
                visited[nextCity] = false;
            }
        }
        return minLength;
    }
};

void processDirectory(const string &directoryPath)
{
    TravelingSalesman tsp;

    for (const auto &entry : fs::directory_iterator(directoryPath))
    {
        const auto &path = entry.path();
        if (entry.is_regular_file() && path.extension() == ".txt")
        { // Chỉ xử lý file .txt
            vector<int> path;
            cout << "Processing file: " << path << endl;
            if (tsp.loadCitiesFromFile(path.string()))
            {
                int optimalLength = tsp.BruteForce(path);
                cout << "Do dai duong di toi uu: " << optimalLength << endl;
                cout << "Chu trinh toi uu: ";
                for (int city : path)
                {
                    cout << city << " ";
                }
                cout << "0\n\n"; // Quay về thành phố ban đầu
            }
            else
            {
                cout << "Could not open file: " << path << endl;
            }
        }
    }
}

int main()
{
    string directoryPath = "path/to/directory"; // Thay thế bằng đường dẫn thực tế của bạn
    processDirectory(directoryPath);
    return 0;
}
