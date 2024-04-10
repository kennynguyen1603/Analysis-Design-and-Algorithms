// TSPSolver.cpp
#include "TSPSolver.h"

void TSPSolver::solveWithACO(const DistanceMatrix &matrix)
{
    ACO aco(matrix);
    aco.solve();
}

void TSPSolver::solveWithGA(const DistanceMatrix &matrix)
{
    GeneticAlgorithm ga(matrix);
    ga.solve();
}

// Triển khai các phương thức khác tương ứng
