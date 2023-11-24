#include <iostream>

using namespace std;

int main(){

	setlocale(LC_ALL, "Russian");
	
	int h, m;
	cin >> h >> m;
	
	cout << endl;

	if(h >= 24 || h < 0 || m < 0 || m >= 60){
		cout << "введены недопустимые данные";
		return 0;
	}
	
	if(h == 0 && m == 0){
		cout << "полночь";
		return 0;
	}
	
	if(h == 12 && m == 0){
		cout << "полдень";
		return 0;
	}
	
	int mod = h % 12 + 12 * (h == 12 || h == 0);
	
	cout << mod << " ";

	if(mod == 1){
		cout << "час";
	}
	else if(mod >= 2 && mod <= 4){
		cout << "часа";
	}
	else{
		cout << "часов";
	}

	if(m != 0){
		cout << " " << m << " ";

		if(m >= 5 && m <= 20){
			cout << "минут ";
		}
		else if(m % 10 == 1){
			cout << "минута ";
		}
		else if(m % 10 >= 2 && m % 10 <= 4){
			cout << "минуты ";
		}
		else{
			cout << "минут ";
		}
	}

	if(h >= 5 && h < 12){
		cout << "утра";
	}
	else if(h >= 5 && h < 18){
		cout << "дня";
	}
	else if(h >= 5 && h <= 23){
		cout << "вечера";
	}
	else{
		cout << "ночи";
	}

	if(m == 0){
		cout << " ровно";
	}

	
	return 0;
}
