#include "TSPSolver.h"
#include "./utility/FileManager.h"
#include <iostream>
using namespace std;
int main()
{
    // Đọc dữ liệu ma trận khoảng cách từ file
    DistanceMatrix matrix = FileManager::readMatrixFromFile("data.txt");

    TSPSolver solver;

    solver.solveWithACO(matrix);

    // solver.solveWithGA(matrix);

    return 0;
}
