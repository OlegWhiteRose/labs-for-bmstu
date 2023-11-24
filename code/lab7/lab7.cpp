#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <string.h>


struct String{
    char* val = new char[0];
    int size = 0;

    String operator+(const String& s) const{
        char* new_s = new char[strlen(val) + strlen(s.val)];

        for(int i = 0; i < strlen(val); ++i){
            new_s[i] = val[i];
        }
        for(int i = strlen(val) - 1; i < strlen(s.val) + strlen(val); ++i){
            new_s[i] = s.val[i - strlen(val) + 1];
        }

        return String{new_s};
    }

    void operator=(const char* s){
        delete []val;

        val = new char[strlen(s)];
        for(int i = 0; i < strlen(s); ++i){
            val[i] = s[i];
        }
    }

    void operator=(const String& s){
        delete []val;

        val = new char[strlen(s.val)];
        for(int i = 0; i < strlen(s.val); ++i){
            val[i] = s.val[i];
        }
    }

    int size(){
        size = strlen(val);
        return size;
    }
};

std::ostream& operator<<(std::ostream& stream, const String& s){
    stream << s.val;
    return stream;        
}

int main(){
    setlocale(LC_ALL, "rus");

    String s, s1;

    s = "lolo";
    s1 = "shka";

    s = s + s1;

    std::cout << s << std::endl;
    std::cout << s.size;

    //std::ifstream key("key.txt"); 

    //char* s = "";
    //while(!key.eof()){
    //    s.getline(a); 
    //}
    //std::cout << a;


    return 0;
}

