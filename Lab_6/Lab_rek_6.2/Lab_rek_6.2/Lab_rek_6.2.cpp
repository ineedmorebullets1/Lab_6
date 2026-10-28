#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

bool isEven(int x)
{
    return x % 2 == 0;
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

// Повертає індекс найменшого парного елемента серед перших n або -1, якщо парних немає
int findMinEvenIndex(const int a[], int n)
{
    if (n == 0) return -1;

    int idx = findMinEvenIndex(a, n - 1);     // найкращий індекс серед перших n - 1

    if (!isEven(a[n - 1]))
        return idx;
    if (idx == -1 || a[n - 1] < a[idx])
        return n - 1;
    return idx;
}

void swapElements(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

// Міняє місцями перший елемент і найменший парний.
// Повертає true, якщо обмін виконано, і false, якщо парних елементів немає.
bool swapFirstWithMinEven(int a[], int n)
{
    int idx = findMinEvenIndex(a, n);
    if (idx == -1)
        return false;
    swapElements(a[0], a[idx]);
    return true;
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const int n = 15, low = -50, high = 50;
    int a[n];

    srand((unsigned)time(nullptr));

    fillArray(a, n, low, high);
    cout << "Початковий масив:" << endl;
    printArray(a, n);
    cout << endl;

    if (swapFirstWithMinEven(a, n))
    {
        cout << "Модифікований масив:" << endl;
        printArray(a, n);
        cout << endl;
    }
    else
    {
        cout << "Парних елементів немає, масив не змінено." << endl;
    }
    return 0;
}