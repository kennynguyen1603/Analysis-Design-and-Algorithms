#include "DistanceMatrix.h"

// DistanceMatrix::DistanceMatrix(int size) : matrix(size, vector<double>(size, 0.0)) {}

DistanceMatrix::DistanceMatrix(int size) : matrix(size, vector<double>(size, 0.0)) {}
void DistanceMatrix::setDistance(int i, int j, double distance)
{
    matrix[i][j] = distance;
    matrix[j][i] = distance;
}

double DistanceMatrix::getDistance(int i, int j) const
{
    return matrix[i][j];
}

int DistanceMatrix::size() const
{
    return matrix.size();
}