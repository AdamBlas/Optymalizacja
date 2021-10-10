#include <iostream>
#include <chrono>
#include <math.h>

using namespace std;

const int SASIN = 70000000;

void eratos(char isPrime[], int index, int byte)
{
    if ((isPrime[index] >> byte) & 1)
    {
        index = index * 8 + byte;
        int step = index;
        int max = SASIN - index;

        while (index < max)
        {
            index += step;
            isPrime[index / 8] &= ~(1 << (index % 8));
        }
    }
}

int main()
{
    auto start_time = std::chrono::system_clock::now();

    int size = ceil((float)SASIN / 8);
    char *isPrime = new char[size];

    for (int i = 0; i < size; i++)
    {
        isPrime[i] = 0xff;
    }

    for (int i = 2; i < size; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            eratos(isPrime, i, j);
        }
    }

    long long sum = 0;
    for (int i = 0; i < size; i++)
    {
        float i8 = i * 8;
        for (int j = 0; j < 8; j++)
        {
            if ((isPrime[i] >> j) & 1)
            {
                sum += i8 + j;
            }
        }
    }

    std::chrono::duration<double> processing_time = std::chrono::system_clock::now() - start_time;
    cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(processing_time).count() << endl;
    cout << "Sum: " << sum << endl;

    if (sum != 139601928199359)
    {
        cout << "ERROR" << endl;
        cout << "DIFF: " << sum - 139601928199359 << endl;
    }

    return 0;
}