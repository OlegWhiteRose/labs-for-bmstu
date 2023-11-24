typedef double (*TPF)(double);

double IntRect(TPF f, double a, double b, double eps, int& n);
double IntTrap(TPF f,double a,double b,double eps,int& n);
void printDividingLine(const char horizontalSybmol, const char connectorSybmol, const int m, const int *wn);
void PrintTabl(struct I_print i_prn[], int k);
double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);