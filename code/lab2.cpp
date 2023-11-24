#include <iostream>

using namespace std;

int main(){

	setlocale(LC_ALL, "Russian");
	
	int h, m;
	cin >> h >> m;
	
	cout << endl;

	if(h >= 24 || h < 0 || m < 0 || m >= 60){
		cout << "������� ������������ ������";
		return 0;
	}
	
	if(h == 0 && m == 0){
		cout << "�������";
		return 0;
	}
	
	if(h == 12 && m == 0){
		cout << "�������";
		return 0;
	}
	
	int mod = h % 12 + 12 * (h == 12 || h == 0);
	
	cout << mod << " ";

	if(mod == 1){
		cout << "���";
	}
	else if(mod >= 2 && mod <= 4){
		cout << "����";
	}
	else{
		cout << "�����";
	}

	if(m != 0){
		cout << " " << m << " ";

		if(m >= 5 && m <= 20){
			cout << "����� ";
		}
		else if(m % 10 == 1){
			cout << "������ ";
		}
		else if(m % 10 >= 2 && m % 10 <= 4){
			cout << "������ ";
		}
		else{
			cout << "����� ";
		}
	}

	if(h >= 5 && h < 12){
		cout << "����";
	}
	else if(h >= 5 && h < 18){
		cout << "���";
	}
	else if(h >= 5 && h <= 23){
		cout << "������";
	}
	else{
		cout << "����";
	}

	if(m == 0){
		cout << " �����";
	}

	
	return 0;
}
