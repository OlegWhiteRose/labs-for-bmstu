#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>
#include <sstream>

using namespace std;

int main(){

    printf("%-12s %-12s %-12s %s \n", "X", "Y(X)", "S(X)", "N");


    long double x = 0;

    while(x < 1 + 1e-5){

        int n = 1;
        long double s = 0;
        long double expected_res = sin(x);
        long double top = x;
        int bottom = 1;

        long double last = top / bottom;

        while( abs(last) > 0.000001 ){

            signed first = -1;
            if((n - 1) % 2 == 0){
                first = 1;
            }

            last = first * (top / bottom);
            s += last;

            top *= x * x;
            bottom *= (2 * n + 1) * (2 * n);


            n += 1;
        }

        n = max(n, 1);


        //output
        ostringstream X_s, Y_s, S_s;

        X_s << fixed; X_s << setprecision(6); X_s << x;
        Y_s << fixed; Y_s << setprecision(6); Y_s << expected_res;
        S_s << fixed; S_s << setprecision(6); S_s << s;

        printf("%-12s %-12s %-12s %d \n", X_s.str().c_str(), Y_s.str().c_str(), S_s.str().c_str(), n);


        x += 0.2;
    }


    return 0;
}

