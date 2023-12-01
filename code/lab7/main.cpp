#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

struct Symbol{
    unsigned char sym;
    unsigned char encoded; 
    int cnt = 0;
    int encoded_cnt = 0;
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
            res[idx] %= 32;
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
        unsigned char key = moduled(c + shifts[idx], 0, 255);
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
        unsigned char key = moduled(c - shifts[idx], 0, 255);
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
        stat[dec].cnt++;
        stat[enc].encoded_cnt++;

        if(stat[dec].cnt == 1){
            stat[dec].sym = dec;
            stat[dec].encoded = enc;
        }
    }

    fenc.close(); fdec.close();

    return stat;
}

void print_table(Symbol* stat, const char* outputfile){
    std::ofstream fout(outputfile);

    fout << "|   символ   |" << std::setw(10);
    fout << "|   кол-во в исх-ом   |" << std::setw(10);
    fout << "|   кол-во в вар-ов   |" << std::setw(10);
    fout << "|   размер блокнота   |" << std::setw(10);
    fout << "|   длина исх-ый   |" << std::setw(10);
    fout << '\n';

    for(int i = 0; i < 256; ++i){
        if(stat[i].cnt > 0 && stat[i].sym){
            std::cout << stat[i].sym << std::endl;
            fout << "|" << stat[i].sym << "           |";
            fout << "|" << stat[i].cnt << "                    |";
            fout << "|" << stat[i].encoded_cnt << "                    |";
            fout << "|" << filesize("key.txt") << "                  |"; 
            fout << "|" << filesize("source.txt") << "                |"; 
            fout << '\n';
        }
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