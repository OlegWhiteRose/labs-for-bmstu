#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <stdio.h>
#include <locale.h>
#include <string.h>

#include "headers.h"
#include "methods.h"

int main() {
    setlocale(LC_ALL, "Russian");
    
    srand(time(NULL));

    double a = rand() % 2;
    double b = rand() % 2 + 2;

    std::cout << "Значение a: " << a << std::endl;
    std::cout << "Значение b: " << b << std::endl;
    std::cout << std::endl;

    typedef double (*pf)(double);
    pf arr[] = {f1, f2, f3, f4};
    char* namef[] = {(char*)"y=x", (char*)"y=sin(22x)", (char*)"y=x^4", (char*)"y=arctg(x)"};
    double exact_val[] = {(b*b - a*a)/2.0, (cos(a*22.0) - cos(b*22.0))/22.0, 
                        (b*b*b*b*b - a*a*a*a*a)/5.0, 
                        b*atan(b) - a*atan(a) - (log(b*b+1) - log(a*a+1))/2.0};

    typedef double (*gf)(TPF, double, double, double, int&);
    gf methods[] = {IntRect, IntTrap};

    I_print* table = new I_print[4];
    for(int i = 0; i < 4; ++i){
        table[i].name = namef[i];
        table[i].i_toch = exact_val[i];
    }

    double epsilons[] = {0.01, 0.001, 0.0001, 0.00001};

    for(int idx = 0; idx < 4; ++idx){
        double eps = epsilons[idx];
        std::cout << "Точность: " << eps;
        std::cout << std::endl;

        for(int g = 0; g < 2; ++g){
            std::cout << "Метод ";

            if(g == 0){
                std::cout << "прямоугольников";
            }
            else{
                std::cout << "трапеций";
            }
            std::cout << std::endl;

            for(int i = 0; i < 4; ++i){
                int n = 1;

                table[i].i_sum = methods[g](arr[i], a, b, eps, n);
                table[i].n = n;
            }
            PrintTabl(table, 4);

            std::cout << std::endl;
        }
    }

    delete[] table;

    return 0;
}
