#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "file_parser.h"
#include "indexer.h"
#include "search_engine.h"

int main() {
    std::string directory = "../test_files";
    FileParser parser;
    auto file_contents = parser.parse_directory(directory);

    if (file_contents.empty()) {
        std::cerr << "No text files found in directory: " << directory << std::endl;
        return 1;
    }

    Indexer indexer;
    indexer.build_index(file_contents);

    SearchEngine engine(file_contents);

    std::string query;
    while (true) {
        std::cout << "\nEnter search query (or type 'exit'): ";
        std::getline(std::cin, query);

        if (query == "exit") break;

        auto results = engine.search(query);
        engine.print_results(results, query);
    }

    return 0;
}
