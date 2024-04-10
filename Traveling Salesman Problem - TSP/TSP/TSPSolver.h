// TSPSolver.h
#include "ACO.h"
#include "GeneticAlgorithm.h"
// Bao gồm các file header khác như BruteForce.h, Backtracking.h nếu có

class TSPSolver
{
public:
    // Các phương thức để chạy các thuật toán khác nhau
    void solveWithACO(const DistanceMatrix &matrix);
    void solveWithGA(const DistanceMatrix &matrix);
    // Thêm các phương thức tương ứng cho các thuật toán khác
};
