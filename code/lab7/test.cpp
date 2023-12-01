#include <iostream>
#include <fstream>
#include <string.h>

int moduled(int n, int l, int r){
    if(n >= l && n <= r) return n;

    if(n < l){
        return r - abs(l - n) % abs(r - l);
    }

    return l + abs(r - n) % abs(r - l);
}


int main(){
    std::ofstream t1("t2.txt");
    std::ifstream t2("t2.txt");

    char c;
    while(t2 >> c){
        t1 << (char)(c - 28);
    }

    t1.close(); t2.close();

    return 0;
}