#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int CUSTOMER_SIZE = 5;
const int VEHICLE_CAPACITY = 10;
const int ANT_COUNT = 10;
const double ALPHA = 1.0;
const double BETA = 5.0;
const double EVAPORATION = 0.5;
const double Q = 100.0;
const int MAX_ITER = 100;

class Customer
{
public:
    int demand;
    int x, y;
    Customer(int x, int y, int demand) : x(x), y(y), demand(demand) {}
};

class Ant
{
public:
    vector<int> tabuList;    // Customers visited
    vector<int> path;        // Path taken
    int remainingCapacity;   // Remaining capacity of the vehicle
    double pathLength = 0.0; // Path length

    Ant() : remainingCapacity(VEHICLE_CAPACITY) {}

    void visitCustomer(int customerIndex, const vector<Customer> &customers)
    {
        if (!visited(customerIndex))
        {
            tabuList.push_back(customerIndex);
            path.push_back(customerIndex);
            remainingCapacity -= customers[customerIndex].demand;
            if (path.size() > 1)
            {
                int prevIndex = path[path.size() - 2];
                pathLength += sqrt(pow(customers[prevIndex].x - customers[customerIndex].x, 2) + pow(customers[prevIndex].y - customers[customerIndex].y, 2));
            }
        }
    }

    bool visited(int customerIndex)
    {
        return find(tabuList.begin(), tabuList.end(), customerIndex) != tabuList.end();
    }

    void clear()
    {
        tabuList.clear();
        path.clear();
        remainingCapacity = VEHICLE_CAPACITY;
        pathLength = 0.0;
    }
};

vector<Customer> customers = {
    Customer(0, 0, 0), // Depot
    Customer(1, 5, 3), Customer(2, 2, 4), Customer(1, -5, 2), Customer(-5, 2, 1), Customer(0, 0, 5)};
vector<Ant> ants(ANT_COUNT);

void initializeAnts()
{
    for (auto &ant : ants)
    {
        ant.clear();
        ant.visitCustomer(0, customers); // Start from the depot
    }
}

void antColonyOptimization()
{
    srand(time(NULL));

    for (int iteration = 0; iteration < MAX_ITER; iteration++)
    {
        initializeAnts();

        for (auto &ant : ants)
        {
            // Here should be the logic for ants to choose the next customer to visit
            // For simplicity, let's assume they visit customers in order until they can't carry more
            for (int i = 1; i < CUSTOMER_SIZE; i++)
            {
                if (ant.remainingCapacity >= customers[i].demand)
                {
                    ant.visitCustomer(i, customers);
                }
            }
            // Return to depot
            ant.visitCustomer(0, customers);
        }

        // Here you would normally update pheromones based on the paths taken
        // For simplicity, this step is omitted

        // Print out the path lengths
        cout << "Iteration " << iteration + 1 << ":" << endl;
        for (int i = 0; i < ANT_COUNT; i++)
        {
            cout << "  Ant " << i + 1 << " Path Length = " << ants[i].pathLength << endl;
        }
    }
}

int main()
{
    antColonyOptimization();
    return 0;
}