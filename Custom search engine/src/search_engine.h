#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>
#include <map>

// This struct holds information about each search result: the file name, the line number, and a score showing how good the match is
struct ScoredResult {
    std::string filename;
    int line_number;
    float score;
};

// This class searches words in the files
class SearchEngine {
private:
    // Stores the content of all files: file name mapped to a list of lines in that file
    std::map<std::string, std::vector<std::string>> file_contents;

public:
    // Takes all files content and saves it for searching
    SearchEngine(const std::map<std::string, std::vector<std::string>>& contents)
        : file_contents(contents) {}

    // It looks for the query word and returns a list of best matches: 'top_k' states how many results to return (default is 10)
    std::vector<ScoredResult> search(const std::string& query, int top_k = 10);
    // Prints the search results
    void print_results(const std::vector<ScoredResult>& results, const std::string& query) const;
};

#endif

