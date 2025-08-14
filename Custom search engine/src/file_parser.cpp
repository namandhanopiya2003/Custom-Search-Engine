#include "file_parser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <dirent.h>
#include <iostream>
#include <cctype>

std::map<std::string, std::vector<std::string>> FileParser::parse_directory(const std::string& path) {
    std::map<std::string, std::vector<std::string>> result;

    DIR* dir = opendir(path.c_str());
    if (!dir) {
        std::cerr << "Failed to open directory: " << path << std::endl;
        return result;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string filename = entry->d_name;
        if (filename == "." || filename == "..") continue;

        std::string full_path = path + "/" + filename;
        std::ifstream infile(full_path.c_str());
        if (!infile.is_open()) continue;

        std::string line;
        std::vector<std::string> lines;
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }

        result[full_path] = lines;
    }

    closedir(dir);
    return result;
}

std::vector<std::string> FileParser::tokenize(const std::string& line) {
    std::istringstream ss(line);
    std::vector<std::string> tokens;
    std::string word;

    while (ss >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
            return !std::isalnum(static_cast<unsigned char>(c));
        }), word.end());

        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (!word.empty()) {
            tokens.push_back(word);
        }
    }

    return tokens;
}
