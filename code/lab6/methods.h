#define COLUMN_NUMBER 4

struct I_print {        // данные для печати результатов интегрирования
    char *name;         // название функции
    double i_sum;       // значение интегральной суммы
    double i_toch;      // точное значение интеграла
    int n;              // число разбиений области интегрирования  при котором достигнута требуемая точность
};

double f1(double x){
    return x;
}

double f2(double x){
    return sin(22 * x);
}

double f3(double x){
    return x * x * x * x;
}

double f4(double x){
    return atan(x);
}


typedef double (*TPF)(double);

double IntRect(TPF f, double a, double b, double eps, int& n){
    double s_prev = -1;
    double s = 0;

    for(;fabs(s - s_prev) > eps && n < 100000; n *= 2){
        s_prev = s;

        double h = (b - a) / n;
        double new_s = 0;
        for(int i = 0; i < n; ++i){
            double l = a + i * h;
            double r = a + (i + 1) * h;
            new_s += f((r + l) / 2.0);
        }

        s = new_s * h;
    }
    n /= 2;

    return s;
}

double IntTrap(TPF f,double a,double b,double eps,int& n){
    double s_prev = -1;
    double s = 0;

    for(;fabs(s - s_prev) > eps && n < 100000; n *= 2){
        s_prev = s;

        double h = (b - a) / n;
        double new_s = 0;
        for(int i = 0; i < n; ++i){
            double l = a + i * h;
            double r = a + (i + 1) * h;
            new_s += (f(r) + f(l)) / 2.0;
        }

        s = new_s * h;
    }
    n /= 2;

    return s;
}


void printDividingLine(const char horizontalSybmol, const char connectorSybmol, const int m, const int *wn) {
    putchar(connectorSybmol);
    for (int line_i = 0; line_i < m; line_i++) {
        for (int line_j = 0; line_j < wn[line_i]; line_j++) {
            putchar(horizontalSybmol);
        }
        putchar(connectorSybmol);
    }
    putchar('\n');
}


void PrintTabl(struct I_print i_prn[], int k) {
    const char SIDE_SYBMOL = '|';
    const char HORIZONTAL_SYBMOL = '-';
    const char CONNECTOR_SYBMOL = '+';

    int wn[COLUMN_NUMBER] = {12, 18, 18, 10};   // ширина столбцов таблицы
    char *title[COLUMN_NUMBER] = {(char *) "Function", (char *) "Integral", (char *) "IntSum", (char *) "N "};
    int size[COLUMN_NUMBER];
    for (int i = 0; i < COLUMN_NUMBER; i++) {
        size[i] = (int) strlen(title[i]);
    }

    // шапка таблицы
    printDividingLine(HORIZONTAL_SYBMOL, CONNECTOR_SYBMOL, COLUMN_NUMBER, wn);

    putchar(SIDE_SYBMOL);
    for (int line_i = 0; line_i < COLUMN_NUMBER; line_i++) {
        int half = (wn[line_i] - size[line_i]) / 2;
        for (int line_j = 0; line_j < half; line_j++) {
            putchar(' ');
        }
        printf("%s", title[line_i]);
        for (int line_j = 0; line_j < half; line_j++) {
            putchar(' ');
        }
        putchar(SIDE_SYBMOL);
    }
    putchar('\n');

    printDividingLine(HORIZONTAL_SYBMOL, CONNECTOR_SYBMOL, COLUMN_NUMBER, wn);

    // заполнение таблицы
    for (int i = 0; i < k; i++) {
        putchar(SIDE_SYBMOL);
        printf("%12s", i_prn[i].name);
        putchar(SIDE_SYBMOL);

        char i_toch[15];
        sprintf(i_toch, "%.10f", i_prn[i].i_toch);
        printf("%18s", i_toch);
        putchar(SIDE_SYBMOL);

        char i_sum[15];
        sprintf(i_sum, "%.10f", i_prn[i].i_sum);
        printf("%18s", i_sum);
        putchar(SIDE_SYBMOL);

        printf("%10d", i_prn[i].n);
        putchar(SIDE_SYBMOL);
        putchar('\n');
        printDividingLine(HORIZONTAL_SYBMOL, CONNECTOR_SYBMOL, COLUMN_NUMBER, wn);
    }
}
