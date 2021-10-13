#include <iostream>
#include <chrono>
#include <math.h>

using namespace std;

const int SASIN = 70000000;

void SieveOfEratosthenes(char isPrime[], int index, int byte)
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

    // Size of array with bit-size bool values
    unsigned int size = ceil((float)SASIN / 8);

    // Array of 8 bit chars, 8 bools per char
    char *isPrime = new char[size];

    // Fill array with 1s
    for (int i = 0; i < size; i++)
    {
        isPrime[i] = 0xff;
    }

    // Use Sieve of Eratosthenes on every number in array

    // Skip two first bits (numbers 0 and 1 as there are not count to prime numbers)
    for (int i = 2; i < 8; i++)
    {
        SieveOfEratosthenes(isPrime, 0, i);
    }

    // Go through all other indexes
    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            SieveOfEratosthenes(isPrime, i, j);
        }
    }

    cout << "Czas: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count() << " ms" << endl;

    // Calculate sum, start from -1 to subtract 1, as it would be counted as prime number
    long long sum = -1;
    for (int i = 0; i < size; i++)
    {
        int i8 = i * 8;
        for (short j = 0; j < 8; j++)
        {
            if ((isPrime[i] >> j) & 1)
            {
                sum += i8 + j;
            }
        }
    }

    cout << "Suma: " << sum << endl;

    long long correctSum = 139601928199359;
    if (sum != correctSum)
    {
        cout << "ERROR" << endl;
        cout << "DIFF: " << sum - correctSum << endl;
    }
    else
    {
        cout << "Suma prawidlowa" << endl;
    }

    return 0;
}