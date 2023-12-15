#include <iostream>
#include <math.h>
#include <iomanip>

int fact(int n){
    if(n <= 1) return 1;

    return fact(n - 1) * n;
}

double** CreateMatrix(int n){
    double** A = new double*[n];
    for(int i = 0; i < n; ++i){
        A[i] = new double[n];
    }

    return A;
}

void FillMatrix(double** A, int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(i == j){
                A[i][j] = 1;
            }
            else if(i < j){
                A[i][j] = pow(1, i) / pow(fact(j), i);
            }
            else{
                A[i][j] = pow(-1, i) / pow(fact(j), i);
            }
        }
    }
}

void MakeCell(double n){
    if(n > 0){
        std::cout << " ";
    }
    if(n < 10){
        std::cout << " ";
    }
    std::cout << n << "  ";
}

void PrintMatrix(double** A, int n, int eps = 0){
    std::cout.unsetf(std::ios_base::fixed);
    if(eps){
        std::cout << std::fixed << std::setprecision(eps);
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            MakeCell(A[i][j]);
        }
        std::cout << '\n';
    }

    std::cout << '\n';
}

void Free(double** A, int n, bool for_static=false){
    for(int i = 0; i < n && !for_static; ++i){
        delete[] A[i];
    }

    delete[] A;
}

int main(){
    int n; const int eps = 5;
    std::cout << "Введите n: "; 
    std::cin >> n;

    double** A = CreateMatrix(n);
    FillMatrix(A, n);
    PrintMatrix(A, n, eps);
    Free(A, n);

    double B[10][10];
    
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            B[i][j] = i * 10 + j;
        }
    }

    double** new_B = new double*[10];
    for (int i = 0; i < 10; i++){
        new_B[i] = B[i];
    }

    PrintMatrix(new_B, 10);
    Free(new_B, 10, true);

    std::cout<<B<<"  "<<B[0]<<"  "<<B[2]<<std::endl;
	std::cout<<B[0][0]<<"  "<<**B <<"  "<<*B[0]<<std::endl;
	std::cout<<*(*(B+1))<<"  "<<*B[1]<<std::endl;
	std::cout<<*(B[0]+1)<<"  " <<*(*B+1)<<std::endl;
	std::cout<<B[0][20]<<"  "<<*(B[0]+20)<<"  "<<*B[2]<<std::endl;

    return 0;
}