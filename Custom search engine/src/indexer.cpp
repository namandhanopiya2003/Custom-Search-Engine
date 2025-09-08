#include "indexer.h"
#include "file_parser.h"

// This function builds the search index from given files (It connects each word to the files where that word appears)
void Indexer::build_index(const std::map<std::string, std::vector<std::string>>& files) {
    FileParser parser;

    // Goes through each file in the input
    std::map<std::string, std::vector<std::string>>::const_iterator it;
    for (it = files.begin(); it != files.end(); ++it) {
        std::string filename = it->first;                                      // It gets the file name
        const std::vector<std::string>& lines = it->second;                    // It gets all lines from that file

        // Goes through each line in the file
        for (size_t i = 0; i < lines.size(); ++i) {
            std::vector<std::string> words = parser.tokenize(lines[i]);        // It breaks line into words

            // Goes through each word in the line
            for (size_t j = 0; j < words.size(); ++j) {
                inverted_index[words[j]].insert(filename);                     // It adds the file name to the set of files for this word
            }
        }
    }
}

// This function gives back the final index (It shows each word and the files where that word is found)
std::map<std::string, std::set<std::string>> Indexer::get_index() {
    return inverted_index;
}

