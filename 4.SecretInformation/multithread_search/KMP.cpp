
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

void DSM::Print() const {
    int sz = _data.size();
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < _data[i].size(); j++) {
            std::cout << _data[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void DSM::CheckFile(fs::path& path, std::queue<std::string>& res) const{
    std::ifstream stream(path);
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
            Word(line, path, str, res);
        }
        str.clear();
    }
}

//std::mutex test;
//
//void DSM::CheckFile(fs::path path, std::vector<std::string>& res) const{
//    std::ifstream stream(path);
//
//    char symbol;
//    int line = 1;
//    int position = 0;
//    bool done = false;
//    std::string str;
//    for (symbol = stream.get(); stream; symbol = stream.get()) {
//        if (symbol == '\n') {
//            if (done == true) {
//                Word(line, path, str, res);
//            }
//            line++;
//            str.clear();
//            done = false;
//            position = 0;
//        } else {
//            str.push_back(symbol);
//        }
//        if (symbol >= _min) {
//            position = _data[symbol - _min][position];
//            if (position == _positionts - 1) {
//                done =  true;
//            }
//        } else {
//            position = 0;
//        }
//    }
//    if (done == true) {
//        Word(line, path, str, res);
//    }
//}

std::mutex Word_guard;

void DSM::Word(int line, fs::path& path, const std::string& str, std::queue<std::string>& res) const {
    //Word_guard.lock();
    //std::cout <</* std::this_thread::get_id() << '\n';*/std::string(path) <<':' << line << " :" << str << std::endl;
    res.push(std::string(path) +":" + std::to_string(line) + " :" + str);
    //Word_guard.unlock();
}


