#include <iostream>
#include "KMP.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "No arguments provided\n";
        return 1;
    } else if (argc < 3) {
        std::cout << "No file to search in provided\n";
        return 1;
    } else if (argc > 3) {
        std::cout << "Too many arguments provided. Expected 2, but " << argc-1 << "provided\n";
        return 1;
    } else {
        std::string filename(argv[2]), pattern(argv[1]);
        if (pattern.length() == 0) {
            std::cout << "Total length of pattern equals zero\n";
            return 1;
        } else {
            DSM searcher(pattern);
            searcher.CheckFile(filename);
            std::cout << "Search ended. Pattern is presented in file " << searcher.GetResult() << " time(s)\n" << std::endl;
        }
    }

    return 0;
}
