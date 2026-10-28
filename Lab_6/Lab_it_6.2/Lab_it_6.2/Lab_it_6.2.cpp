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
    for (int i = 0; i < n; i++)
        a[i] = low + rand() % (high - low + 1);
}

void printArray(const int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << setw(4) << a[i];
    cout << endl;
}

// Повертає індекс найменшого парного елемента або -1, якщо парних немає
int findMinEvenIndex(const int a[], int n)
{
    int idx = -1;
    for (int i = 0; i < n; i++)
        if (isEven(a[i]) && (idx == -1 || a[i] < a[idx]))
            idx = i;
    return idx;
}

void swapElements(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

// Міняє місцями перший елемент і найменший парний.
// Повертає true, якщо парний елемент є (обмін виконано), інакше false.
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

    if (swapFirstWithMinEven(a, n))
    {
        cout << "Модифікований масив:" << endl;
        printArray(a, n);
    }
    else
    {
        cout << "Парних елементів немає, масив не змінено." << endl;
    }
    return 0;
}