#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

template <typename T> struct Vector{
    T* arr;
    int capacity = 1;
    int size = 0;
    int k = 2;

    Vector(){
        arr = new T[capacity];
    }

    void push_back(T data){
        if (size == capacity) {
            T* temp = new T[k * capacity];

            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }

            delete[] arr;
            capacity *= k;
            arr = temp;
        }

        arr[size] = data;
        size++;
    }

    void push_back(T data, int index){

        if (index == capacity){
            push_back(data);
        }
        else{
            arr[index] = data;
        }
    }

    void pop_back() { 
        size--;
    }

    T operator[](int ind){
        return arr[ind];
    }
};

struct Symbol{
    Vector<unsigned char> encoded;
    int cnt = 0;

    void add(const unsigned char& enc){
        encoded.push_back(enc);
    }
};

int words_cnt(const char* filename){
    std::ifstream fin(filename, std::ios::binary);

    int cnt = 0;
    while(!fin.eof()){
        char* s = new char[1000];
        fin >> s;
        cnt++;
    } cnt--;

    fin.close();

    return cnt;
}

int* caesar_shifts(const char* filename, int length){
    std::ifstream fin(filename, std::ios::binary);

    int* res = new int[length];

    int idx = 0;
    unsigned char* s = new unsigned char[1000];
    fin >> s;
    while(!fin.eof()){
        for(int i = 0; i < strlen((char*)s); ++i){
            res[idx] += s[i];
        }

        idx++; fin >> s;
    }

    delete []s; fin.close();

    return res;
}

void encode(int* shifts, int shifts_cnt, const char* inputfile, const char* outputfile){
    std::ifstream fin(inputfile, std::ios::binary);
    std::ofstream fout(outputfile, std::ios::binary);

    int idx = 0; unsigned char c = fin.get();
    while(fin.tellg() != EOF){      
        unsigned char key = (c + shifts[idx]) % 256;
        fout << key;

        idx++; idx = idx % shifts_cnt;
        c = fin.get();
    }

    fin.close(); fout.close();
}

void decode(int* shifts, int shifts_cnt, const char* inputfile, const char* outputfile){
    std::ifstream fin(inputfile, std::ios::binary);
    std::ofstream fout(outputfile, std::ios::binary);
 
    int idx = 0; unsigned char c = fin.get();
    while(fin.tellg() != EOF){      
        unsigned char key = (c - shifts[idx]) % 256;
        fout << key;

        idx++; idx = idx % shifts_cnt;
        c = fin.get();
    }

    fin.close(); fout.close();
}

Symbol* creating_table(const char* sourcefile, const char* encodedfile){
    std::ifstream fenc(encodedfile, std::ios::binary);
    std::ifstream fdec(sourcefile, std::ios::binary);

    Symbol* stat = new Symbol[256];
    unsigned char enc = fenc.get(), dec = fdec.get(); 
    while(fenc.tellg() != EOF && fdec.tellg() != EOF){
        if(dec < 208){
            stat[dec].add(enc);
        }

        enc = fenc.get(); dec = fdec.get();
    }

    fenc.close(); fdec.close();

    return stat;
}

int length(int num){
    if(num == 0){
        return 1;
    }

    int res = 0;
    while(num > 0){
        res += 1;
        num /= 10;
    }

    return res;
}

void make_cell(int num, std::ofstream &fout){
    int len = length(num);  
    
    fout << ' ';
    int spc = 3 - len;   
    for(int i = 0; i < spc; ++i){
        fout << ' ';
    }
    fout << num;
}

void print_table(Symbol* stat, const char* outputfile){
    std::ofstream fout(outputfile, std::ios::binary);

    int** table = new int*[256];
    for(int i = 0; i < 256; ++i){
        table[i] = new int[256];
        for(int j = 0; j < 256; ++j){
            table[i][j] = 0;
        }
    }

    //верхняя часть
    fout << "     ";
    for(int i = 0; i < 256; ++i){
        if (stat[i].encoded.size == 0) continue;
        make_cell(i, fout);

        for(int j = 0; j < stat[i].encoded.size; ++j){
            table[i][stat[i].encoded[j]]++;
        }
    }
    fout << '\n';


    for(int j = 0; j < 256; ++j){
        bool flag = false;
        for(int i = 0; i < 256; ++i){
            if(table[i][j]) flag = true;
        }
        if(!flag) continue;

        make_cell(j, fout);
        for(int i = 0; i < 256; ++i){
            if(stat[i].encoded.size == 0) continue;
            make_cell(table[i][j], fout);
        }
        fout << '\n';
    }

    fout.close();
}

int main(){
    setlocale(LC_ALL, "rus"); 
    
    int length = words_cnt("key.txt");
    int* shifts = caesar_shifts("key.txt", length);
    int shifts_cnt = words_cnt("key.txt");

    encode(shifts, shifts_cnt, "source.txt", "encoded.txt");
    decode(shifts, shifts_cnt, "encoded.txt", "decoded.txt");

    delete []shifts;

    Symbol* stat = creating_table("source.txt", "encoded.txt");
    print_table(stat, "table.txt");

    delete []stat;

    return 0;
}