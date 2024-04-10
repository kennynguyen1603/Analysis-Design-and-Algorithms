#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <limits.h>

using namespace std;

// Number of cities in TSP
#define V 5

// Initial population size for the algorithm
#define POP_SIZE 10

// Structure of a GNOME
struct individual
{
    string gnome;
    int fitness;
};

// Function to return a random number from start and end
int rand_num(int start, int end)
{
    int r = end - start;
    int rnum = start + rand() % r;
    return rnum;
}

// Function to check if the character has already occurred in the string
bool repeat(string s, char ch)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ch)
            return true;
    }
    return false;
}

// Function to return a mutated GNOME
string mutatedGene(string gnome)
{
    while (true)
    {
        int r = rand_num(1, V);
        int r1 = rand_num(1, V);
        if (r1 != r)
        {
            char temp = gnome[r];
            gnome[r] = gnome[r1];
            gnome[r1] = temp;
            break;
        }
    }
    return gnome;
}

// Function to return a valid GNOME string
string create_gnome()
{
    string gnome = "0";
    while (true)
    {
        if (gnome.size() == V)
        {
            gnome += gnome[0];
            break;
        }
        int temp = rand_num(1, V);
        if (!repeat(gnome, (char)(temp + 48)))
            gnome += (char)(temp + 48);
    }
    return gnome;
}

// Function to return the fitness value of a gnome.
int cal_fitness(string gnome, const vector<vector<int>> &map)
{
    int f = 0;
    for (int i = 0; i < gnome.size() - 1; i++)
    {
        f += map[gnome[i] - '0'][gnome[i + 1] - '0'];
    }
    return f;
}

// Function to return the updated value of the cooling element.
int cooldown(int temp)
{
    return (90 * temp) / 100;
}

// Comparator for GNOME struct.
bool lessthan(const individual &t1, const individual &t2)
{
    return t1.fitness < t2.fitness;
}

// Utility function for TSP problem.
void TSPUtil(const vector<vector<int>> &map)
{
    // Generation Number
    int gen = 1;
    // Number of Gene Iterations
    int gen_thres = 5;

    vector<individual> population;
    individual temp;

    // Populating the GNOME pool.
    for (int i = 0; i < POP_SIZE; i++)
    {
        temp.gnome = create_gnome();
        temp.fitness = cal_fitness(temp.gnome, map);
        population.push_back(temp);
    }

    cout << "\nInitial population: " << endl
         << "GNOME    FITNESS VALUE\n";
    for (int i = 0; i < POP_SIZE; i++)
        cout << population[i].gnome << " "
             << population[i].fitness << endl;
    cout << "\n";

    bool found = false;
    int temperature = 10000;

    // Iteration to perform population crossing and gene mutation.
    while (temperature > 1000 && gen <= gen_thres)
    {
        sort(population.begin(), population.end(), lessthan);
        cout << "\nCurrent temp: " << temperature << "\n";
        vector<individual> new_population;

        for (int i = 0; i < POP_SIZE; i++)
        {
            individual p1 = population[i];

            while (true)
            {
                string new_g = mutatedGene(p1.gnome);
                individual new_gnome;
                new_gnome.gnome = new_g;
                new_gnome.fitness = cal_fitness(new_gnome.gnome, map);

                if (new_gnome.fitness <= population[i].fitness)
                {
                    new_population.push_back(new_gnome);
                    break;
                }
                else
                {
                    // Accepting the rejected children at a possible probability above threshold.
                    float prob = pow(2.7, -1 * ((float)(new_gnome.fitness - population[i].fitness) / temperature));
                    if (prob > 0.5)
                    {
                        new_population.push_back(new_gnome);
                        break;
                    }
                }
            }
        }

        temperature = cooldown(temperature);
        population = new_population;
        cout << "Generation " << gen << " \n";
        cout << "GNOME    FITNESS VALUE\n";

        for (int i = 0; i < POP_SIZE; i++)
            cout << population[i].gnome << " "
                 << population[i].fitness << endl;
        gen++;
    }
}

int main()
{
    const char *filepath = "input.txt"; // Đường dẫn đến tệp chứa ma trận
    ifstream infile(filepath);
    if (!infile)
    {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    vector<vector<int>> map(V, vector<int>(V, 0));
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            infile >> map[i][j];
    infile.close();

    TSPUtil(map);

    return 0;
}
