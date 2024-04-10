#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "DistanceMatrix.h"
#include <string>
using namespace std;

class FileManager
{
public:
    static DistanceMatrix readMatrixFromFile(const string &fileName);
};

#endif // FILEMANAGER_H