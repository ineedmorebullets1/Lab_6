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
    if (n == 0) return;
    fillArray(a, n - 1, low, high);
    a[n - 1] = low + rand() % (high - low + 1);
}

void printArray(const int a[], int n)
{
    if (n == 0) return;
    printArray(a, n - 1);
    cout << setw(4) << a[n - 1];
}

int countSatisfying(const int a[], int n)
{
    if (n == 0) return 0;
    return countSatisfying(a, n - 1) + (isSatisfying(a[n - 1]) ? 1 : 0);
}

int sumSatisfying(const int a[], int n)
{
    if (n == 0) return 0;
    return sumSatisfying(a, n - 1) + (isSatisfying(a[n - 1]) ? a[n - 1] : 0);
}

void zeroSatisfying(int a[], int n)
{
    if (n == 0) return;
    zeroSatisfying(a, n - 1);
    if (isSatisfying(a[n - 1]))
        a[n - 1] = 0;
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
    cout << endl;

    cout << "Кількість: " << countSatisfying(b, n) << endl;
    cout << "Сума: " << sumSatisfying(b, n) << endl;

    zeroSatisfying(b, n);
    cout << "Модифікований масив:" << endl;
    printArray(b, n);
    cout << endl;
    return 0;
}