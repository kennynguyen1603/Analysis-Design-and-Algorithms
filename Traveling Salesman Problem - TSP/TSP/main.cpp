// main.cpp
#include "TSPSolver.h"
#include "FileManager.h"

int main()
{
    // Đọc dữ liệu ma trận khoảng cách từ file
    DistanceMatrix matrix = FileManager::readMatrixFromFile("data.txt");

    TSPSolver solver;

    // Chọn thuật toán để giải quyết bài toán
    solver.solveWithACO(matrix);

    // solver.solveWithGA(matrix);

    return 0;
}
