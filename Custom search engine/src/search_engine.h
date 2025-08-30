#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>
#include <map>

struct ScoredResult {
    std::string filename;
    int line_number;
    float score;
};

class SearchEngine {
private:
    std::map<std::string, std::vector<std::string>> file_contents;

public:
    SearchEngine(const std::map<std::string, std::vector<std::string>>& contents)
        : file_contents(contents) {}

    std::vector<ScoredResult> search(const std::string& query, int top_k = 10);
    void print_results(const std::vector<ScoredResult>& results, const std::string& query) const;
};

#endif
