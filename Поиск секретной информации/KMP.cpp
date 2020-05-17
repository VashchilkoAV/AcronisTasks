//
// Created by alexander on 17.05.2020.
//

#include "KMP.h"


#include "KMP.h"




DSM::DSM(const std::string &str) {
    std::vector<int> pi = prefix_func(str);
    unsigned sizeOfAutomat = pi.size() + 1;
    _positionts = sizeOfAutomat;
    uint8_t size_of_alphabet = _max-_min+1;
    _data.resize(size_of_alphabet);
    for (uint8_t symbol = 0; symbol < size_of_alphabet; symbol++) {
        _data[symbol].resize(sizeOfAutomat);
        for (int position = 0; position < sizeOfAutomat; position++) {
            int cursor = position;
            if (cursor == 0) {
                _data[symbol][cursor] = str[0] == symbol + _min ? 1 : 0;
            } else {
                while (str[cursor] != symbol + _min && cursor != 0) {
                    cursor = pi[cursor - 1];
                }
                _data[symbol][position] = str[cursor] == symbol + _min ? cursor + 1 : cursor;
            }
        }

    }
}

std::vector<int> DSM::prefix_func(const std::string & str) const {
    int n = (int)str.length();
    std::vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int k = pi[i - 1];
        while (k > 0 && str[i] != str[k]) {
            k = pi[k - 1];
        }
        if (str[i] == str[k]) {
            k++;
        }
        pi[i] = k;
    }
    return pi;
}

void DSM::CheckFile(const std::string& filename) {
    std::ifstream stream(filename);
    if (!stream.is_open()) {
        std::cout << "Can not open file \"" << filename << "\" for read.\n";
    }
    char symbol;
    int line = 0;
    int position = 0;
    bool done = false;
    std::string str;
    str.reserve(1024*1024);
    while (getline(stream, str, '\n')) {
        position = 0;
        done = false;
        line++;
        for (int i = 0; i < str.length(); i++) {
            symbol = str[i];
            if (symbol >= _min) {
                position = _data[symbol - _min][position];
                if (position == _positionts - 1) {
                    done =  true;
                }
            } else {
                position = 0;
            }
        }
        if (done == true) {
            Word(line, filename, str);
        }
        str.clear();
    }
}

void DSM::Word(int line, const std::string& filename, const std::string& str) {
    std::cout << filename << ":" << std::to_string(line) << " :" << str << "\n";
    _result++;
}

