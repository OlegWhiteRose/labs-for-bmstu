#include <iostream>
#include <fstream>
#include <string.h>

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
    char* s = new char[50];
    while(!fin.eof()){
        fin >> s;

        for(int i = 0; i < strlen(s); ++i){
            res[idx] += s[i];
            res[idx] %= 128;
        }

        idx++;
    }

    delete []s; fin.close();

    return res;
}

void encode(int* shifts, int shifts_cnt, const char* inputfile, const char* outputfile){
    std::ifstream fin(inputfile);
    std::ofstream fout(outputfile);

    int idx = 0; char c;
    while(fin >> c){
        char key = moduled(c + shifts[idx], -127, 127);
        fout << key;

        idx++; idx = idx % shifts_cnt;
    }

    fin.close(); fout.close();
}

void decode(int* shifts, int shifts_cnt, const char* inputfile, const char* outputfile){
    std::ifstream fin(inputfile);
    std::ofstream fout(outputfile);
 
    int idx = 0; char c;
    while(fin >> c){      
        char key = moduled(c - shifts[idx], -127, 127);
        fout << key;

        idx++; idx = idx % shifts_cnt;
    }

    fin.close(); fout.close();
}

int main(){
    setlocale(LC_ALL, "rus"); 
    
    int length = words_cnt("key.txt");
    int* shifts = caesar_shifts("key.txt", length);

    encode(shifts, words_cnt("key.txt"), "source.txt", "encoded.txt");
    decode(shifts, words_cnt("key.txt"), "encoded.txt", "decoded.txt");

    delete []shifts;

    return 0;
}