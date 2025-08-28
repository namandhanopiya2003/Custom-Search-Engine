#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include <vector>
#include <map>

class FileParser {
public:
    std::map<std::string, std::vector<std::string>> parse_directory(const std::string& path);
    std::vector<std::string> tokenize(const std::string& line);
};

#endif
