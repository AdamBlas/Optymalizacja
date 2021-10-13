#include <iostream>
#include <chrono>
#include <math.h>

using namespace std;

const int BITS = 31;

int main()
{
    long long sum = 0;
    int amount = (BITS - 1) * BITS * 0.5;
    int index = 0;
    auto start_time = std::chrono::system_clock::now();
    unsigned int* arr = new unsigned int[amount];

    for (int i = 0; i < BITS - 1; i++)
    {
        for (int j = i + 1; j < BITS; j++)
        {
            arr[index++] = (1 << i) + (1 << j);
        }
    }

    std::chrono::duration<double> processing_time = std::chrono::system_clock::now() - start_time;
    cout << "Czas: " << std::chrono::duration_cast<std::chrono::milliseconds>(processing_time).count() << " ms" << endl;
    cout << "Czas: " << std::chrono::duration_cast<std::chrono::nanoseconds>(processing_time).count() << " ns" << endl;

    for (int i = 0; i < amount; i++)
    {
        sum += arr[i];
    }

    cout << "Suma: " << sum << endl;

    long long correctSum = 64424509410;
    if (sum != correctSum)
    {
        cout << "ERROR" << endl;
        cout << "DIFF: " << sum - correctSum << endl;
    }
    else
    {
        cout << "Suma prawidlowa" << endl;
    }

    delete[] arr;

    return 0;
}
