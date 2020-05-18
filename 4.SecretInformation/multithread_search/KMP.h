#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <mutex>
#include <thread>
#include "file_manager.h"





class DSM {
public:
    DSM(const std::string&);
    void Print() const;
    void CheckFile(fs::path&, std::queue<std::string>&) const;
private:
    unsigned _positionts = 0;
    void Word(int, fs::path&, const std::string&, std::queue<std::string>&) const;
    const uint8_t _min = 32, _max = 127;
    std::vector<std::vector<int>> _data;
    std::vector<int> prefix_func(const std::string&) const;
};