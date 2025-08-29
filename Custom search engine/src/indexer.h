#ifndef INDEXER_H
#define INDEXER_H

#include <map>
#include <string>
#include <vector>
#include <set>

class Indexer {
public:
    void build_index(const std::map<std::string, std::vector<std::string>>& files);
    std::map<std::string, std::set<std::string>> get_index();

private:
    std::map<std::string, std::set<std::string>> inverted_index;
};

#endif
