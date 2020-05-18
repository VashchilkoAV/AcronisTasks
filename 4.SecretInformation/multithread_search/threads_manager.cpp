#include "threads_manager.h"


Config GetConfig(int argc, char** argv) {
    Config result;
    for (int i = 1; i < argc; i++) {
        switch (argv[i][0]) {
            case '-':
                if (argv[i][1]) {
                    if (argv[i][1] == 'n') {
                        result.mode = 0;
                    } else if (argv[i][1] == 't') {
                        std::string thr_num(argv[i]);
                        std::stringstream str(thr_num);
                        str.ignore(2);
                        str >> result.threads;
                    }
                }
                break;
            case '/':
                result.start_dir = std::string(argv[i]);
                break;
            default:
                result.sequence = std::string(argv[i]);
        }
    }
    return result;
}

void InitCalculations(const Config &config) {
    DSM au1(config.sequence);
    fs::path p(config.start_dir);
    FileManager fm(p, config.mode, config.threads);
    ThreadsManager Thr(config.threads-1, fm, au1);
    SearchFunc(fm, au1);
    Thr.Join();
}

std::mutex for_search;

void SearchFunc(FileManager & fm, DSM& automat) {
    std::queue<std::string> result;
    std::queue<fs::path> storage;
    fs::path file;
    int num_files = fm.GetCurrentNum();
    while (!fm.IsEmpty()) {

        for_search.lock();
        for (int i = 0; i < num_files; i++) {
            if (!fm.IsEmpty()) {
                storage.push(fm.GetFile());
            }
        }
//        fs::path file = fm.GetFile();
        for_search.unlock();
        for (int i = 0; i < num_files; i++) {
            if (!storage.empty()) {
                automat.CheckFile(storage.front(), result);
                storage.pop();
            }
        }
        if (for_search.try_lock() == true) {
            while (!result.empty()) {
                std::cout << result.front() << std::endl;
                result.pop();
            }
            for_search.unlock();
        }

//        automat.CheckFile(file, result);




    }


    for_search.lock();
    while (!result.empty()) {
        std::cout << result.front() << std::endl;
        result.pop();
    }
    for_search.unlock();
//    do {
//        bool f = 1;
//        fs::path file;
//        for_search.lock();
//        if (fm.IsEmpty() == 0) {
//            file = fm.GetFile();
//        }
//        else {
//            f = 0;
//        }
//        for_search.unlock();
//        if (f == 0) {
//            break;
//        }
//        automat.CheckFile(file);
//
//    } while (1);
}

ThreadsManager::ThreadsManager(const int num, FileManager & fm, DSM& automat) {
    num_threads = num;
    for (int i = 0; i < num; i++) {
        _data.push_back(std::thread(SearchFunc, std::ref(fm), std::ref(automat)));
    }
}
