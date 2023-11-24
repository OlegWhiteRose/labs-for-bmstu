#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

#include "methods.h"
#include "headers.h"


int main()
{
  setlocale(LC_ALL, "Russian");

  const int N_MAX = 100000;
  long double eps1 = 0.000001, eps2 = 0.00000001;

  step(6, 1, eps1, N_MAX);
  step(8, 1, eps2, N_MAX);
  step(6, 10, eps1, N_MAX);
  step(8, 10, eps2, N_MAX);

  return 0;
}




