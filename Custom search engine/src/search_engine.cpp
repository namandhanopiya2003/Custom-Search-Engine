#include "search_engine.h"
#include <sstream>
#include <map>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <windows.h>
#include <cmath>

// Calculates how different two words are by counting the smallest number of changes needed
int levenshtein_distance(const std::string& s1, const std::string& s2) {
    size_t m = s1.size(), n = s2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    // Initializing the first row and column
    for (size_t i = 0; i <= m; ++i) dp[i][0] = static_cast<int>(i);
    for (size_t j = 0; j <= n; ++j) dp[0][j] = static_cast<int>(j);

    // Filling the matrix with minimum changes needed
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];                                                  // No change needed if letters match
            else
                dp[i][j] = std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;      // Min changes + 1
        }
    }
    return dp[m][n];
}

// Checks if two words are close enough to be considered a fuzzy match
bool is_fuzzy_match(const std::string& word, const std::string& query, int threshold = 1) {
    return levenshtein_distance(word, query) <= threshold;
}

// Searches for the query word in all files and lines, including fuzzy matches
std::vector<ScoredResult> SearchEngine::search(const std::string& query, int top_k) {
    std::vector<ScoredResult> results;

    // Converts the search query to lowercase to make search case-insensitive
    std::string lowered_query = query;
    std::transform(lowered_query.begin(), lowered_query.end(), lowered_query.begin(), ::tolower);

    std::map<std::string, int> fuzzy_match_counts;
    bool exact_match_found = false;

    // Loops through all files and lines to find matches
    for (const auto& pair : file_contents) {
        const std::string& file = pair.first;
        const std::vector<std::string>& lines = pair.second;

        for (size_t i = 0; i < lines.size(); ++i) {
            std::string line = lines[i];
            std::string word;
            std::istringstream iss(line);

            int total_words = 0;                 // It counts words in the line
            int match_count = 0;                 // It counts matches in the line

            // It checks each word in the line
            while (iss >> word) {
                ++total_words;

                std::string lowered_word = word;
                std::transform(lowered_word.begin(), lowered_word.end(), lowered_word.begin(), ::tolower);

                if (lowered_word == lowered_query) {
                    ++match_count;
                    exact_match_found = true;
                }
                else if (is_fuzzy_match(lowered_word, lowered_query)) {
                    ++match_count;
                    fuzzy_match_counts[lowered_word]++;
                }
            }

            // If there was at least one match, it calculates a score and save the result
            if (match_count > 0) {
                float score = static_cast<float>(match_count) / total_words;
                results.push_back({file, static_cast<int>(i + 1), score});
            }
        }
    }

    // If no exact match found but there are fuzzy matches, it suggests the closest match
    if (!exact_match_found && !fuzzy_match_counts.empty()) {
        std::string best_suggestion;
        int max_count = 0;
        for (const auto& pair : fuzzy_match_counts) {
            if (pair.second > max_count) {
                best_suggestion = pair.first;
                max_count = pair.second;
            }
        }

        if (best_suggestion != lowered_query) {
            std::cout << "Spelling error, replaced with \"" << best_suggestion << "\"\n";
        }
    }

    // Sorts results by score (highest first)
    std::sort(results.begin(), results.end(), [](const ScoredResult& a, const ScoredResult& b) {
        return a.score > b.score;
    });

    // If top_k is set, it will keep only that many results
    if (top_k > 0 && results.size() > static_cast<size_t>(top_k)) {
        results.resize(top_k);
    }

    return results;
}

// It prints the search results nicely formatted
void SearchEngine::print_results(const std::vector<ScoredResult>& results, const std::string& query) const {
    std::cout << "\nFetching results";
    for (int i = 0; i < 3; ++i) {
        Sleep(400);                                           // Wait for 0.4 seconds to show loading effect
        std::cout << "." << std::flush;
    }
    Sleep(400);
    std::cout << "\n\n";

    // If no results, it informs the user
    if (results.empty()) {
        std::cout << "No results found for: " << query << "\n";
        return;
    }

    std::cout << "\nRanked Results:\n";
    int rank = 1;
    for (const auto& result : results) {
        // Prepares the header with file name, line number, and score
        std::ostringstream header;
        header << "[" << rank++ << "] "
               << "FILE_SOURCE: " << result.filename
               << "      ||      LINE_NO: " << result.line_number
               << "      ||      SIMILARITY_SCORE: " << std::fixed << std::setprecision(3) << result.score;

        // Gets the line text where the match was found
        const std::string& matched_line = file_contents.at(result.filename)[result.line_number - 1];

        // Breaks the line into words
        std::istringstream iss(matched_line);
        std::vector<std::string> words;
        std::string word;
        while (iss >> word) words.push_back(word);

        // Converts query to lowercase for matching
        std::string lowered_query = query;
        std::transform(lowered_query.begin(), lowered_query.end(), lowered_query.begin(), ::tolower);

        // Creates a snippet showing a few words around the matching word
        std::string snippet = "... ";
        for (size_t i = 0; i < words.size(); ++i) {
            std::string lowered_word = words[i];
            std::transform(lowered_word.begin(), lowered_word.end(), lowered_word.begin(), ::tolower);
            if (is_fuzzy_match(lowered_word, lowered_query)) {
                size_t start = (i >= 2) ? i - 2 : 0;
                size_t end = std::min(i + 3, words.size());
                for (size_t j = start; j < end; ++j) {
                    snippet += words[j] + " ";
                }
                snippet += "...";
                break;
            }
        }

        std::string content = "MATCHED_TEXT: " + snippet;

        // Creates a border to make output look organized
        int width = std::max(header.str().size(), content.size()) + 4;
        std::string border = "+" + std::string(width, '-') + "+";

        // Prints the bordered output
        std::cout << border << "\n";
        std::cout << "| " << std::left << std::setw(width - 1) << header.str() << "|\n";
        std::cout << "| " << std::left << std::setw(width - 1) << content << "|\n";
        std::cout << border << "\n\n";
    }
}

