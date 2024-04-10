#ifndef ACO_H
#define ACO_H

#include "DistanceMatrix.h"
#include <vector>

class ACO
{
public:
    ACO(const DistanceMatrix &matrix, int numAnts, int maxIterations, double alpha, double beta, double evaporationRate, double initialPheromone);
    void solve();

private:
    const DistanceMatrix &matrix;
    int numAnts;
    int maxIterations;
    double alpha;
    double beta;
    double evaporationRate;
    double initialPheromone;
    std::vector<std::vector<double>> pheromones;

    void initializePheromones();
    int selectNextCity(int ant, const std::vector<bool> &visited, int currentCity);
    double calculateProbability(int ant, int city, const std::vector<bool> &visited);
    double calculatePathLength(const std::vector<int> &path);
    void updatePheromones(const std::vector<std::vector<int>> &paths);
};

#endif // ACO_H
