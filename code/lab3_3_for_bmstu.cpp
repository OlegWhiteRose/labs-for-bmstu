#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

int main(){
    cout << fixed << setprecision(6);

    cout << "X" << setw(16) << "Y(X)" << setw(13) << "S(X)" << setw(10) << "N" << endl;
    //printf("%-12s %-12s %-12s %s \n", "X", "Y(X)", "S(X)", "N");


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

        //output_for_bmstu
        cout << x << setw(5) << "";
        cout << expected_res << setw(5) << "";
        cout << s << setw(5) << "";
        cout << n << endl;


        x += 0.2;
    }


    return 0;
}

