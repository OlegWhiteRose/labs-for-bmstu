pair<long double, int> method1(long double eps, int k, int n_max){
  int n = 0;

  long double l = -1 * k;
  long double r = 1 * k;

  long double prev_x = l;
  long double x = r;

  for(;abs(x - prev_x) > eps;){
    if(n + 1 > n_max){
        break;
    }
    n += 1;

    prev_x = x;
    x = x - (x - k * cos(x));
  }

  return {x, n};
}

pair<long double, int> method2(long double eps, int k, int n_max){
  int n = 0;

  long double l = -1 * k;
  long double r = 1 * k;

  for(;r - l > eps;){
    if(n + 1 > n_max){
        break;
    }
    n += 1;

    long double mid = (r + l) / 2;
    long double res = mid - k * cos(mid);

    if(res >= 0){
      r = mid;
    }
    else{
      l = mid + eps;
    }
  }

  return {l, n};
}

pair<long double, int> method3(long double eps, int k, int n_max){
  int n = 0;

  long double l = -1 * k;
  long double r = 1 * k;  

  long double prev_x = l;
  long double x = r;

  for(;abs(x - prev_x) > eps;){
    if(n + 1 > n_max){
        break;
    }
    n += 1;

    prev_x = x;
    x = x - (x - k * cos(x)) / (1 + k * sin(x));
  }

  return {x, n};
}

void begin_words(int setf, int k, long double eps){
    cout << fixed << setprecision(setf);

    cout << "Уравнение: x - " << k << "*cos(x) = 0. Погрешность: " << eps << endl;
    cout << "Метод " << setw(4) << "x " << setw(12) << "n" << endl;
}

int length(int n){
    int t = 0;
    for(;n > 0;){
        t++;
        n /= 10;
    }

    return t;
}

long double saveout(pair<long double, int> out, int& saver){
    saver = length(out.second);
    return out.first; 
}

void step(int setf, int k, long double eps, int N_MAX){
    begin_words(setf, k, eps);
    
    int saver, space_cnt = 3;

    if(abs(eps - 0.000001) < 0.00000001){
        space_cnt += 2;
    }

    cout << "1. " << setw(5) << " " << saveout(method1(eps, k, N_MAX), saver) << setw(space_cnt + saver);
    cout << method1(eps, k, N_MAX).second << endl;

    cout << "2. " << setw(5) << " " << saveout(method2(eps, k, N_MAX), saver) << setw(space_cnt + saver);
    cout << method2(eps, k, N_MAX).second << endl;

    cout << "3. " << setw(5) << " " << saveout(method3(eps, k, N_MAX), saver) << setw(space_cnt + saver);
    cout << method3(eps, k, N_MAX).second << endl;

    cout << endl;
}
