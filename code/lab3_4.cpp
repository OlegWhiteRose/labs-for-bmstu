#include <iostream>

using namespace std;

int main(){

  setlocale(LC_ALL, "Russian");

  bool request = true;

  do {
    int x, n; 
    
    //input
    cout << "Введите x: ";
    cin >> x; cout << endl;
    cout << "Введите n: ";
    cin >> n; cout << endl;


    long double y = 1;
    long long top = 1;
    long long bottom = 1;

    for(int i = 2; i <= n; ++i){
        
        signed first = 1;
        if(i % 2 == 0){
            first = -1;
        }
        
        top *= x * x;
        bottom *= (2 * (i - 1)) * (2 * (i - 1) - 1);

        long double last = (top / (bottom + 0.0)) * first;

        y += last;

        if(i == n){
            continue;
        }

        if(i == 3 || i == 5 || i == 10){
            cout << "Результат при n = " << i << ": " << y << endl;
        }
    }

    cout << "Результат: " << y << endl;

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
