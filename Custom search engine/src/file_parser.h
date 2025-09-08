#ifndef FILE_PARSER_H
#define FILE_PARSER_H
// These are needed to use strings, lists, and maps in the code
#include <string>
#include <vector>
#include <map>

// This class helps read files and break text into words
class FileParser {
public:
    // This function reads all files in a folder (It returns a map where each file is linked to its list of lines)
    std::map<std::string, std::vector<std::string>> parse_directory(const std::string& path);
    // This function breaks a line of text into clean words (no symbols and all lowercase)
    std::vector<std::string> tokenize(const std::string& line);
};

#endif

