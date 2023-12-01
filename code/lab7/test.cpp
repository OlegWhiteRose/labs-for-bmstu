#include <iostream>
#include <fstream>
#include <string.h>


int main(){
    std::ofstream t1("t1.txt");

    t1 << 'a';
    t1.close();

    return 0;
}