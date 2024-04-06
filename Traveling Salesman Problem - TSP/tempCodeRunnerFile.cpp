#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

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

    void loadCitiesFromFile(const string &fileName)
    {
        ifstream file(fileName);
        if (!file.is_open())
        {
            cerr << "Khong the mo file: " << fileName << endl;
            return;
        }

        string line;
        bool startReading = false;

        while (getline(file, line))
        {
            // Bỏ qua cho đến khi gặp NODE_COORD_SECTION
            if (line.find("NODE_COORD_SECTION") != string::npos)
            {
                startReading = true;
                continue;
            }

            // Dừng đọc khi gặp EOF
            if (line.find("EOF") != string::npos || file.eof())
                break;

            if (startReading)
            {
                istringstream iss(line);
                int id, x, y;
                iss >> id >> x >> y; // Bỏ qua id vì không sử dụng trong bài toán TSP này
                cities.push_back({x, y});
            }
        }
        file.close();
    }

    int BruteForce(vector<int> &path)
    {
        vector<bool> visited(cities.size(), false);
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

int main()
{
    TravelingSalesman tsp;
    tsp.loadCitiesFromFile("cities.txt");

    vector<int> path;
    int optimalLength = tsp.BruteForce(path);

    cout << "Do dai duong di toi uu: " << optimalLength << endl;
    cout << "Chu trinh toi uu: ";
    for (int city : path)
    {
        cout << city << " ";
    }
    cout << "0\n"; // Quay về thành phố ban đầu

    return 0;
}
