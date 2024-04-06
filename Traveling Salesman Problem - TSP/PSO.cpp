#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <ctime>
#include <numeric>
using namespace std;

const int MAX_CITIES = 10;
const int MAX_PARTICLES = 30;
const int MAX_ITERATIONS = 1000;
const double V_MAX = 4; // Giới hạn tốc độ để tránh vận tốc quá cao

struct City
{
    int x, y;
};

vector<City> cities(MAX_CITIES);

double distance(int city1, int city2)
{
    return sqrt(pow(cities[city1].x - cities[city2].x, 2) + pow(cities[city1].y - cities[city2].y, 2));
}

class Particle
{
public:
    vector<int> position;
    vector<double> velocity;
    vector<int> best_position;
    double best_fitness;

    Particle()
    {
        position.resize(MAX_CITIES);
        velocity.resize(MAX_CITIES, 0);
        best_position.resize(MAX_CITIES);
        iota(position.begin(), position.end(), 0);        // Khởi tạo vị trí ban đầu
        random_shuffle(position.begin(), position.end()); // Xáo trộn vị trí để tạo lộ trình ngẫu nhiên
        best_position = position;
        best_fitness = numeric_limits<double>::max();
    }
};

double calculateFitness(vector<int> &solution)
{
    double totalDistance = 0;
    for (int i = 0; i < MAX_CITIES - 1; i++)
    {
        totalDistance += distance(solution[i], solution[i + 1]);
    }
    totalDistance += distance(solution[MAX_CITIES - 1], solution[0]);
    return totalDistance;
}

void updateVelocity(Particle &particle, vector<int> &gBest)
{
    // Đơn giản hóa mô hình cập nhật vận tốc cho mô hình PSO trong không gian hoán vị
    for (int i = 0; i < MAX_CITIES; i++)
    {
        particle.velocity[i] += ((double)rand() / RAND_MAX) * (particle.best_position[i] - particle.position[i]) +
                                ((double)rand() / RAND_MAX) * (gBest[i] - particle.position[i]);
        // Giới hạn vận tốc
        if (particle.velocity[i] > V_MAX)
        {
            particle.velocity[i] = V_MAX;
        }
        else if (particle.velocity[i] < -V_MAX)
        {
            particle.velocity[i] = -V_MAX;
        }
    }
}

void updatePosition(Particle &particle)
{
    // Áp dụng biến đổi dựa trên vận tốc để thay đổi vị trí
    // Lưu ý: Cách tiếp cận này chỉ mang tính chất minh họa và có thể không phản ánh đúng cách PSO hoạt động trong không gian hoán vị
    for (int i = 0; i < MAX_CITIES; i++)
    {
        if (particle.velocity[i] > 0)
        {
            int j = (i + 1) % MAX_CITIES;
            swap(particle.position[i], particle.position[j]);
        }
    }
}

void optimize(vector<Particle> &swarm, vector<int> &gBest, double &gBestFitness)
{
    for (int iter = 0; iter < MAX_ITERATIONS; iter++)
    {
        for (auto &particle : swarm)
        {
            updateVelocity(particle, gBest);
            updatePosition(particle);
            double fitness = calculateFitness(particle.position);
            if (fitness < particle.best_fitness)
            {
                particle.best_fitness = fitness;
                particle.best_position = particle.position;
                if (fitness < gBestFitness)
                {
                    gBestFitness = fitness;
                    gBest = particle.position;
                }
            }
        }
    }
}

int main()
{
    srand(time(0));
    for (auto &city : cities)
    {
        city.x = rand() % 100;
        city.y = rand() % 100;
    }

    vector<Particle> swarm(MAX_PARTICLES);
    vector<int> globalBest(MAX_CITIES);
    double globalBestFitness = numeric_limits<double>::max();

    optimize(swarm, globalBest, globalBestFitness);

    cout << "Optimal tour: ";
    for (int city : globalBest)
    {
        cout << city << " ";
    }
    cout << "\nTotal distance: " << globalBestFitness << endl;

    return 0;
}
