#include <iostream>
#include <math.h>
#include <iomanip>

const int CONSOLE_LENGTH = 60;

int fact(int n){
    if(n <= 1) return 1;

    return fact(n - 1) * n;
}

double** CreateMatrix(int n, int m){
    double** A = new double*[n];
    for(int i = 0; i < n; ++i){
        A[i] = new double[m];
    }

    return A;
}

void FillMatrix(double** A, int n, int m){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
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

void MakeCell(double n, int eps, int type){
    if(n > 0 && type == 2){
        std::cout << " ";
    }
    if(n < 10){
        std::cout << " ";
    }

    if(type == 1){
        if(n < 0) std::cout << "-";
        if(n > 0) std::cout << " ";
        char c = (int)'0' + eps;

        char* a = new char[6];
        a[0] = '%'; a[1] = '1'; a[2] = '0'; a[3] = '.'; a[4] = c; a[5] = 'e';
        
        printf((const char*)a, fabs(n));
    }
    else{
        std::cout << n << "  ";
    }
}

void PrintLine(){
    for(int i = 0; i < CONSOLE_LENGTH; ++i){
        std::cout << '-';
    }
}

void PrintMatrix(double** A, int n, int m, int eps = 0, int type = 0){
    std::cout << std::endl;

    int el_size = 0;
    if(eps){
        if(type == 1){
            el_size = 5 + eps;
        }
        else{
            el_size = 2 + eps;
        }
    }

    std::cout.unsetf(std::ios_base::fixed);
    if(eps){
        if(type == 1){
            std::cout << "Научный тип" << std::endl;
        }
        else{
            std::cout << "Математический тип" << std::endl;
            std::cout << std::fixed << std::setprecision(eps);
        }
    }


    int line;
    if(!eps){
        line = m;
    }
    else{
        line = CONSOLE_LENGTH / el_size;
    }

    for(int k = 0;;++k){
        for(int i = 0; i < n; ++i){
            for(int j = k * line; j < std::min((k + 1) * line, m); ++j){
                MakeCell(A[i][j], eps, type);
            }
            std::cout << std::endl;
        }

        if(k * line >= m){
            return;
        }

        std::cout << std::endl;
        PrintLine();
        std::cout << std::endl;
    }
}

void Free(double** A, int n, bool for_static=false){
    for(int i = 0; i < n && !for_static; ++i){
        delete[] A[i];
    }

    delete[] A;
}

struct Data{
    int p1, p2, p3, p4;
};

auto StartMessages(){
    int n, m;
    std::cout << "Введите n: "; 
    std::cin >> n;
    std::cout << "Введите m: ";
    std::cin >> m;
    
    int type;
    std::cout << "Если нужен научный вывод - введите 1, если математический - введите 2: ";
    std::cin >> type;

    int eps;
    std::cout << "Введите точность: ";
    std::cin >> eps;

    return Data{n, m, eps, type};
}

int main(){
    auto [n, m, eps, type] = StartMessages();

    double** A = CreateMatrix(n, m);
    FillMatrix(A, n, m);
    PrintMatrix(A, n, m, eps, type);
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

    PrintMatrix(new_B, 10, 10);
    Free(new_B, 10, true);

    std::cout << sizeof(double) << std::endl;
    std::cout<< B <<"  " << std::endl;
    int s; std::cin >> s;
    std::cout << B[1]<<"  "<<*B + 2<<std::endl;
    std::cin >> s;
	std::cout<<&(*(B[4] - 1))<<"  "<<*(B + 4) <<"  "<<*(B + 3) + 6<<std::endl;
    std::cin >> s;
	std::cout<<*(*(B+3) - 1)<<"  "<<*B[2] - 10<<std::endl;
    std::cin >> s;
	std::cout<<(B[2]-3)<<"  " <<*(*B+7)<<std::endl;
    std::cin >> s;
	std::cout<<B[5][21]<<"  "<<*(B[2]-13)<<"  "<<*B[2]<<std::endl;

    return 0;
}