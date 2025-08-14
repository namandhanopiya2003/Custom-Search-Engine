#include "indexer.h"
#include "file_parser.h"

void Indexer::build_index(const std::map<std::string, std::vector<std::string>>& files) {
    FileParser parser;

    std::map<std::string, std::vector<std::string>>::const_iterator it;
    for (it = files.begin(); it != files.end(); ++it) {
        std::string filename = it->first;
        const std::vector<std::string>& lines = it->second;

        for (size_t i = 0; i < lines.size(); ++i) {
            std::vector<std::string> words = parser.tokenize(lines[i]);

            for (size_t j = 0; j < words.size(); ++j) {
                inverted_index[words[j]].insert(filename);
            }
        }
    }
}

std::map<std::string, std::set<std::string>> Indexer::get_index() {
    return inverted_index;
}
