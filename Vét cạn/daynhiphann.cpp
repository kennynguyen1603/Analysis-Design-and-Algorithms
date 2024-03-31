#include <iostream>
#include <vector>
using namespace std;

void generateBinary(int n, vector<int> &binary, int i)
{
    if (i == n)
    {
        for (int j = 0; j < binary.size() - 1; j++)
        {
            if (binary[j] == 1 && binary[j + 1] == 1)
                return;
        }

        for (int j = 0; j < binary.size(); j++)
        {
            cout << binary[j];
        }
        cout << "\n";
        return;
    }

    binary[i] = 0;
    generateBinary(n, binary, i + 1);

    binary[i] = 1;
    generateBinary(n, binary, i + 1);
}

int main()
{
    int n;
    cout << "Enter n: ";
    cin >> n;

    vector<int> binary(n);
    generateBinary(n, binary, 0);
    return 0;
}