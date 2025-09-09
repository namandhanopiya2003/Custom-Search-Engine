#ifndef INDEXER_H
#define INDEXER_H
// Includes for using maps, sets, strings, and vectors
#include <map>
#include <string>
#include <vector>
#include <set>

// This class helps keep track of words and the files where those words appear
class Indexer {
public:
    // This function goes through all files and makes a list (The list connects each word to the files that have that word)
    void build_index(const std::map<std::string, std::vector<std::string>>& files);
    // This function gives back the full list made above (It tells which files contain each word)
    std::map<std::string, std::set<std::string>> get_index();

private:
    // This is where the word-to-file list is saved inside the class (For each word, it keeps a set of file names where the word appears)
    std::map<std::string, std::set<std::string>> inverted_index;
};

#endif

