#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

bool isSatisfying(int x)
{
    return !(x > 0 && x % 5 == 0);
}

void fillArray(int a[], int n, int low, int high)
{
    for (int i = 0; i < n; i++)
        a[i] = low + rand() % (high - low + 1);
}

void printArray(const int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << setw(4) << a[i];
    cout << endl;
}

int countSatisfying(const int a[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        if (isSatisfying(a[i]))
            count++;
    return count;
}

int sumSatisfying(const int a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        if (isSatisfying(a[i]))
            sum += a[i];
    return sum;
}

void zeroSatisfying(int a[], int n)
{
    for (int i = 0; i < n; i++)
        if (isSatisfying(a[i]))
            a[i] = 0;
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    const int n = 22, low = -40, high = 50;
    int b[n];

    srand((unsigned)time(nullptr));

    fillArray(b, n, low, high);
    cout << "Початковий масив:" << endl;
    printArray(b, n);

    cout << "Кількість: " << countSatisfying(b, n) << endl;
    cout << "Сума: " << sumSatisfying(b, n) << endl;

    zeroSatisfying(b, n);
    cout << "Модифікований масив:" << endl;
    printArray(b, n);
    return 0;
}