#include <iostream>
#include <vector>
using namespace std;

void baitoandoitien(int N)
{
    vector<int> menhgiatien = {
        100000,
        50000,
        20000,
        10000,
    };
    //    1000};

    vector<int>
        sototienmoimenhgia(menhgiatien.size(), 0);

    int sotiensaumoilandoi = N;

    for (int i = 0; i < menhgiatien.size(); i++)
    {
        if (sotiensaumoilandoi >= menhgiatien[i])
        {
            sototienmoimenhgia[i] = sotiensaumoilandoi / menhgiatien[i];
            sotiensaumoilandoi -= sototienmoimenhgia[i] * menhgiatien[i];
        }
    }

    cout << "Co the rut so tien " << N << " voi ca menh gia tien: " << endl;
    int total = 0;
    for (int i = 0; i < sototienmoimenhgia.size(); i++)
    {
        if (sototienmoimenhgia[i] > 0)
        {
            cout << sototienmoimenhgia[i] << " to " << menhgiatien[i] << endl;
            total += sototienmoimenhgia[i];
        }
    }
    cout << "tong so to la: " << total;
}

int main()
{
    int N;
    cout << "Nhap so tien can rut: ";
    cin >> N;

    baitoandoitien(N);
    return 0;
}