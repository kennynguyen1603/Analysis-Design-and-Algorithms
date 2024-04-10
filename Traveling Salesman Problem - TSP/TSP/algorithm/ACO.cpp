#include "ACO.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
ACO::ACO(const DistanceMatrix &matrix, int numAnts, int maxIterations, double alpha, double beta, double evaporationRate, double initialPheromone)
    : matrix(matrix), numAnts(numAnts), maxIterations(maxIterations), alpha(alpha), beta(beta), evaporationRate(evaporationRate), initialPheromone(initialPheromone) {}

void ACO::solve()
{
    srand(time(nullptr));
    initializePheromones();

    for (int iteration = 0; iteration < maxIterations; ++iteration)
    {
        std::vector<std::vector<int>> paths(numAnts);
        for (int ant = 0; ant < numAnts; ++ant)
        {
            std::vector<bool> visited(matrix.size(), false);
            int currentCity = rand() % matrix.size();
            paths[ant].push_back(currentCity);

            for (int i = 1; i < matrix.size(); ++i)
            {
                int nextCity = selectNextCity(ant, visited, currentCity);
                paths[ant].push_back(nextCity);
                visited[nextCity] = true;
                currentCity = nextCity;
            }
        }

        updatePheromones(paths);
    }
}

void ACO::initializePheromones()
{
    pheromones.resize(matrix.size(), std::vector<double>(matrix.size(), initialPheromone));
}

int ACO::selectNextCity(int ant, const std::vector<bool> &visited, int currentCity)
{
    double totalProbability = 0.0;
    std::vector<double> probabilities(matrix.size(), 0.0);

    for (int city = 0; city < matrix.size(); ++city)
    {
        if (!visited[city])
        {
            probabilities[city] = calculateProbability(ant, city, visited);
            totalProbability += probabilities[city];
        }
    }

    double randomValue = ((double)rand() / RAND_MAX) * totalProbability;
    double cumulativeProbability = 0.0;

    for (int city = 0; city < matrix.size(); ++city)
    {
        if (!visited[city])
        {
            cumulativeProbability += probabilities[city];
            if (cumulativeProbability >= randomValue)
            {
                return city;
            }
        }
    }

    return -1; // Không thể chọn thành phố tiếp theo
}

double ACO::calculateProbability(int ant, int city, const std::vector<bool> &visited)
{
    double pheromone = pheromones[paths[ant].back()][city];
    double visibility = 1.0 / matrix.getDistance(paths[ant].back(), city);
    return pow(pheromone, alpha) * pow(visibility, beta);
}

double ACO::calculatePathLength(const std::vector<int> &path)
{
    double length = 0.0;
    for (int i = 0; i < path.size() - 1; ++i)
    {
        length += matrix.getDistance(path[i], path[i + 1]);
    }
    return length;
}

void ACO::updatePheromones(const std::vector<std::vector<int>> &paths)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix.size(); ++j)
        {
            pheromones[i][j] *= (1.0 - evaporationRate);
        }
    }

    for (int ant = 0; ant < numAnts; ++ant)
    {
        double pathLength = calculatePathLength(paths[ant]);
        for (int i = 0; i < paths[ant].size() - 1; ++i)
        {
            int from = paths[ant][i];
            int to = paths[ant][i + 1];
            pheromones[from][to] += 1.0 / pathLength;
            pheromones[to][from] += 1.0 / pathLength;
        }
    }
}
