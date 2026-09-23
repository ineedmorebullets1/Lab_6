#include <iostream>
using namespace std;
int main()
{
	cout << "Good bye!" << endl;
	int p = 1;
	int i = 1;
	while (i <= 10)
	{
		p *= i;
		i++;
	};

	cout << "p = " << p << " i = " << i << endl;
	system("pause");
	return 0;
}