#include "file_parser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <dirent.h>
#include <iostream>
#include <cctype>

// This function reads all the files in a folder (It saves each file's content as a list of lines)
std::map<std::string, std::vector<std::string>> FileParser::parse_directory(const std::string& path) {
    std::map<std::string, std::vector<std::string>> result;        // To store file name and its lines

    // Tries to open the folder
    DIR* dir = opendir(path.c_str());
    if (!dir) {
        std::cerr << "Failed to open directory: " << path << std::endl;         // Show error if folder can't be opened
        return result;
    }

    struct dirent* entry;
    // Goes through each file in the folder
    while ((entry = readdir(dir)) != NULL) {
        std::string filename = entry->d_name;
        // It skips current (".") and parent ("..") folder entries
        if (filename == "." || filename == "..") continue;

        // Creates the full file path
        std::string full_path = path + "/" + filename;
        // Tries to open the file
        std::ifstream infile(full_path.c_str());
        if (!infile.is_open()) continue;                                        // Skips if can't open the file

        std::string line;
        std::vector<std::string> lines;
        // Reads the file line by line and stores each line
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }

        // Adds the file and its lines to the result
        result[full_path] = lines;
    }

    // Closes the folder when completed
    closedir(dir);
    return result;
}

// This function breaks line of text into words
std::vector<std::string> FileParser::tokenize(const std::string& line) {
    std::istringstream ss(line);
    std::vector<std::string> tokens;
    std::string word;

    // Goes through each word in the line
    while (ss >> word) {
        // Removes characters that are not letters or numbers
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
            return !std::isalnum(static_cast<unsigned char>(c));                // Keeps only letters and numbers
        }), word.end());

        // Turns the words into lowercase
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        // It only adds the word if it's not empty
        if (!word.empty()) {
            tokens.push_back(word);
        }
    }

    return tokens;
}

