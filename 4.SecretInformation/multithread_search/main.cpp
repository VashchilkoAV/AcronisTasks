#include <iostream>

#include "threads_manager.h"


namespace fs=std::filesystem;

int main(int argc, char**argv) {
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    //std::ios::sync_with_stdio(false);

    Config config = GetConfig(argc, argv);
    if (config.sequence.empty()) {
        std::cout << "No string to search\n";
        return 1;
    }
    InitCalculations(config);


    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << duration << '\n';
    return 0;
}