#include <curses.h>
#include <string.h>

template<typename T, typename P> struct Pair{
    T first;
    P second;
};

Pair<Pair<char*, int>*, int> Read(){
    int maxcnt = 1000, maxsize = 1000;

    Pair<char*, int>* arr = new Pair<char*, int>[maxcnt];
    for(int i = 0; i < maxcnt; ++i){
        arr[i].first = new char[maxsize];
    }

    char c = getchar(), buf[maxsize];
    int idx = 0, ind = 0;
    while(c != '.'){
        if(c == ' '){
            if(ind != 0){
                for(int i = 0; i < ind; ++i){
                    arr[idx].first[i] = buf[i];
                }
                arr[idx].second = ind;
                idx++;
            }
            ind = 0;
        }
        else{
            buf[ind] = c;
            ind++;
        }

        c = getchar(); 
    }
    if(ind != 0){
        for(int i = 0; i < ind; ++i){
            arr[idx].first[i] = buf[i];
        }
        arr[idx].second = ind;
        idx++;
    }

    return Pair<Pair<char*, int>*, int>{arr, idx};
}

bool equal(Pair<char*, int> &lhs, Pair<char*, int> &rhs){
    if(lhs.second != rhs.second) return false;

    int size = lhs.second;
    for(int i = 0; i < size; ++i){
        if(lhs.first[i] != rhs.first[i]) return false;
    }
    return true;
}

void Output(Pair<char*, int> &c){
    int skip = -1;
    if(c.second % 2 != 0 && c.second != 1){
        skip = c.second / 2;
    }

    for(int i = 0; i < c.second; ++i){
        if(i != skip){
            putchar(c.first[i]);
        }
    }

    putchar('\n');
}

void Write(Pair<Pair<char*, int>*, int> &s){
    for(int i = 0; i < s.second - 1; ++i){
        if(!equal(s.first[i], s.first[s.second - 1])){
            Output(s.first[i]);
        }
    }
}

int main(){

    Pair<Pair<char*, int>*, int> s = Read();
    Write(s);

    return 0;
}