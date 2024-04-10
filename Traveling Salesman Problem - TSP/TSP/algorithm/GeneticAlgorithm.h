#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "DistanceMatrix.h"
#include <vector>

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(const DistanceMatrix &matrix);
    void solve();

private:
    DistanceMatrix matrix;
    // Thêm các thuộc tính và phương thức cần thiết
};

#endif // GENETICALGORITHM_H
