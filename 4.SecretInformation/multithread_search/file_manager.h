#pragma once

#include <queue>
#include <string>
#include <filesystem>


namespace fs = std::filesystem;


class FileManager {
public:
    FileManager(const fs::path&, bool, int num_threads);
    fs::path GetFile();
    bool IsEmpty() const {return _data.empty();}
    void AddRes(const std::string& );
    int GetCurrentNum();
private:
    std::queue<fs::path> _data;
    std::queue<std::string> _result;
    void Recursive(const fs::path&);
    void NonRecursive(const fs::path&);
    int _num_threads;
};