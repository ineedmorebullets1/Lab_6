// Lab_02.cpp
// Дергачев Назар Денисович
// Лабораторна робота № 2.
// Лінійні програми.
// Варіант 6

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double alpha;  // кут у градусах
    double a;      // кут у радіанах
    double z1;     // результат обчислення 1-го виразу
    double z2;     // результат обчислення 2-го виразу

    cout << "alpha = ";
    cin >> alpha;

    // Переведення градусів у радіани
    a = alpha * acos(-1.0) / 180.0;

    // Обчислення за першою формулою
    z1 = cos(a) + cos(2 * a) + cos(6 * a) + cos(7 * a);

    // Обчислення за другою формулою
    z2 = 4 * cos(a / 2) * cos(5 * a / 2) * cos(4 * a);

    cout << endl;
    cout << "z1 = " << z1 << endl;
    cout << "z2 = " << z2 << endl;

    return 0;
}