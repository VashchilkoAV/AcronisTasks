#pragma once
#include "KMP.h"
#include "file_manager.h"

#include <thread>
#include <mutex>
#include <vector>
#include <sstream>
//#include <pthread.h>

struct Config {
    bool mode=1;
    int threads=1;
    std::string start_dir=".";
    std::string sequence = "";
};

class ThreadsManager{
public:
    void Join() {
        for (int i = 0; i < num_threads; i++) {
            _data[i].join();
        }
    }


    ThreadsManager(const int num, FileManager & fm, DSM& automat);

private:
    std::vector<std::thread> _data;
    int num_threads;
};

Config GetConfig(int argc, char** argv);
void InitThreads(const int num, FileManager & fm, DSM& automat);
void InitCalculations(const Config& config);
void SearchFunc(FileManager&, DSM&);
