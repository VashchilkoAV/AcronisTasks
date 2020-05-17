#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <filesystem>

namespace fs = std::filesystem;




class DSM {
public:
    DSM(const std::string&);
    void CheckFile(const std::string& filename);
    unsigned long long GetResult() {return _result;}
private:
    unsigned long long _result = 0;
    unsigned _positionts = 0;
    const uint8_t _min = 32, _max = 127;
    std::vector<std::vector<int>> _data;
    std::vector<int> prefix_func(const std::string&) const;
    void Word(int line, const std::string& filename, const std::string& str);
};