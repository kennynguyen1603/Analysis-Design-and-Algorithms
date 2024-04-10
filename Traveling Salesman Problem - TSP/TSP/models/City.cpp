#include "City.h"
#include <cmath>

City::City(int id, double x, double y) : id(id), x(x), y(y) {}

double City::distanceTo(const City &other) const
{
    double dx = x - other.x;
    double dy = y - other.y;
    return sqrt(dx * dx + dy * dy);
}
