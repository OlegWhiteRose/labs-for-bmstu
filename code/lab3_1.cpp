#include <iostream>

using namespace std;

int main() {

	setlocale(LC_ALL, "Russian");

	bool request = true;

	do {
		//input
		int n, m;

		cout << "Введите n: ";
		cin >> n;

		cout << "Введите m: ";
		cin >> m;

		cout << endl;

		//functional code
		long long s = 0;

		for (int i = 5; i <= n; i += 5) {
			if (i % m != 0) {
				s += i;
			}
		}

		//output
		cout << s << endl;

		//request
		cout << "Желаете продолжить работу? (y/n)" << endl;

		char answer; cin >> answer;

		if (answer != 'y') {
			request = false;
		}

		cout << endl;

	} while (request);


	return 0;
}
