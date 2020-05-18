//
// Created by alex on 9/28/19.
//

#include "file_manager.h"

FileManager::FileManager(const fs::path & path, bool is_rec, int num_threads) {
    _num_threads = num_threads;
    if (is_rec == true) {
        Recursive(path);
    }
    else {
        NonRecursive(path);
    }
}



fs::path FileManager::GetFile() {
    fs::path path = _data.front();
    _data.pop();
    return path;
}

void FileManager::NonRecursive(const fs::path& start_dir) {
    if (fs::exists(start_dir) && fs::is_directory(start_dir)) {
        for (const auto& entry_point : fs::directory_iterator(start_dir)) {
            if (fs::is_regular_file(entry_point.path())) {
                _data.push(entry_point.path());
            }
        }
    }
}

void FileManager::Recursive(const fs::path& start_dir) {
    if (fs::exists(start_dir) && fs::is_directory(start_dir)) {
        for (auto& entry_point : fs::recursive_directory_iterator(start_dir, fs::directory_options::skip_permission_denied)) {
            if (fs::is_regular_file(entry_point.path())) {
                _data.push(entry_point);
            }
        }
    }
}

void FileManager::AddRes(const std::string &str) {
    _result.push(str);
}

int FileManager::GetCurrentNum() {
    if (_data.size() < 100) {
        return _data.size()/_num_threads;
    }
    else if (_data.size() < 1000000){
        return 1000;
    } else {
        return 10000;
    }
    //return _data.size()/_num_threads;
}

//void FileManager::Recursive(const fs::path& start_dir) {
//    if (fs::exists(start_dir) && fs::is_directory(start_dir)) {
//        for (auto& entry_point : fs::directory_iterator(start_dir)) {
//            if (fs::is_regular_file(entry_point.path())) {
//                _data.push(entry_point);
//            } else if (fs::is_directory(entry_point.path())) {
//                Recursive(entry_point);
//            }
//        }
//    }
//}
