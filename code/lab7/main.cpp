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
    unsigned char sym;
    Vector<unsigned char> encoded;
    int cnt = 0;

    void add(const unsigned char& enc){
        encoded.push_back(enc);
    }
};

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);

    int res = in.tellg();
    in.close();

    return res;
}

int moduled(int n, int l, int r){
    if(n >= l && n <= r) return n;

    if(n < l){
        return r - abs(l - n) % abs(r - l);
    }

    return l + abs(r - n) % abs(r - l);
}

int words_cnt(const char* filename){
    std::ifstream  fin(filename);

    int cnt = 0;
    while(!fin.eof()){
        char* s = new char[50];
        fin >> s;
        cnt++;
    }

    fin.close();

    return cnt;
}

int* caesar_shifts(const char* filename, int length){
    std::ifstream fin(filename);

    int* res = new int[length];

    int idx = 0;
    unsigned char* s = new unsigned char[50];
    while(!fin.eof()){
        fin >> s;

        for(int i = 0; i < strlen((char*)s); ++i){
            res[idx] += s[i];
        }

        idx++;
    }

    delete []s; fin.close();

    return res;
}

void encode(int* shifts, int shifts_cnt, const char* inputfile, const char* outputfile){
    std::ifstream fin(inputfile);
    std::ofstream fout(outputfile);

    int idx = 0; unsigned char c;
    while(fin >> c){        
        unsigned char key = (c + shifts[idx]) % 256;
        fout << key;

        idx++; idx = idx % shifts_cnt;
    }

    fin.close(); fout.close();
}

void decode(int* shifts, int shifts_cnt, const char* inputfile, const char* outputfile){
    std::ifstream fin(inputfile);
    std::ofstream fout(outputfile);
 
    int idx = 0; unsigned char c;
    while(fin >> c){      
        unsigned char key = (c - shifts[idx]) % 256;
        fout << key;

        idx++; idx = idx % shifts_cnt;
    }

    fin.close(); fout.close();
}

Symbol* creating_table(const char* sourcefile, const char* encodedfile){
    std::ifstream fenc(encodedfile);
    std::ifstream fdec(sourcefile);

    Symbol* stat = new Symbol[256];
    unsigned char enc, dec;
    while(fenc >> enc && fdec >> dec){
        if(dec == 208) continue;

        stat[dec].sym = dec;
        stat[dec].add(enc);
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
    
    fout << '|';
    int spc = 3 - len;   
    for(int i = 0; i < spc; ++i){
        fout << ' ';
    }
    fout << num << '|';
}

void print_table(Symbol* stat, const char* outputfile){
    std::ofstream fout(outputfile);

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
        make_cell((int)stat[i].sym, fout);

        for(int j = 0; j < stat[i].encoded.size; ++j){
            table[stat[i].sym][stat[i].encoded[j]]++;
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

    encode(shifts, words_cnt("key.txt"), "source.txt", "encoded.txt");
    decode(shifts, words_cnt("key.txt"), "encoded.txt", "decoded.txt");

    delete []shifts;

    Symbol* stat = creating_table("source.txt", "encoded.txt");
    print_table(stat, "table.txt");

    delete []stat;

    return 0;
}