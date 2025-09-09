#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "file_parser.h"
#include "indexer.h"
#include "search_engine.h"

int main() {
    // Folder where the text files are stored
    std::string directory = "../test_files";
    // Create a FileParser object to read files
    FileParser parser;
    // Read all files in the folder
    auto file_contents = parser.parse_directory(directory);

    // If no files are found, show an error and stop the program
    if (file_contents.empty()) {
        std::cerr << "No text files found in directory: " << directory << std::endl;
        return 1;
    }

    Indexer indexer;                                                 // Creates an Indexer object to build the word index
    indexer.build_index(file_contents);                              // Builds the index from the files

    SearchEngine engine(file_contents);                              // Creates a SearchEngine to handle user queries

    std::string query;
    while (true) {
        // Asks user for a search word or phrase
        std::cout << "\nEnter search query (or type 'exit'): ";
        // Reads the whole line user types
        std::getline(std::cin, query);

        // If user types 'exit', stop the program
        if (query == "exit") break;

        // Searches for the query and get the results
        auto results = engine.search(query);
        // Shows the search results to the user
        engine.print_results(results, query);
    }

    return 0;
}

