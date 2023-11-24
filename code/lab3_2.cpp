#include <iostream>
#include <iomanip>

using namespace std;

int main() {

	setlocale(LC_ALL, "Russian");

	//input

	long double a; 
	
	cout << "Введите a: ";
	cin >> a;
	cout << endl;

	//functional code

	long double res = 1;

	if (a >= 0) {
		for (int i = 2; i <= 8; i += 2) {
			res *= i * i;
		}
		res -= a;
	}
	else {
		for (int i = 3; i <= 9; i += 3) {
			res *= i - 2;
		}
	}


	cout << setprecision(7) << res;

	return 0;
}
