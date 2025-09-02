## 🔍 CUSTOM SEARCH ENGINE

## 🧠 ABOUT THIS PROJECT ==>

- A C++-based command-line search engine that efficiently retrieves relevant lines from multiple large text files using keyword and fuzzy search.

- Implements inverted indexing to enable fast keyword lookup across files.

- Supports ranking results by relevance using TF-IDF scoring.

- Includes fuzzy matching to correct user typos and suggest the most probable intended word.

---

## ⚙ TECHNOLOGIES USED ==>

- **C++**

- **Standard Template Library (STL)**

- **File Handling**

- **Unordered Maps / Vectors / Sets**

- **String Matching Algorithms**

---

## 📁 PROJECT FOLDER STRUCTURE ==>

CustomSearchEngine/
├── src/
│   ├── main.cpp              # Main entry point; handles input, initializes engine, and shows results
│   ├── file_parser.cpp       # Logic to read and parse text files into line-wise structure
│   ├── file_parser.h         # Header for file parser; defines classes and functions used in parsing
│   ├── indexer.cpp           # Builds inverted index: maps words to file, line, and frequency
│   ├── indexer.h             # Header for indexer; defines data structures and methods for indexing
│   ├── search_engine.cpp     # Implements search logic, fuzzy matching, and result ranking
│   └── search_engine.h       # Header for search engine; declares fuzzy search and scoring functions
│
├── test_files/
│   ├── sample  1.txt         # Sample document used for search testing and indexing
│   ├── sample  2.txt         # Another sample file for broader keyword coverage
│   │   ...
│   └── sample 25.txt         # Up to 25 documents supported; can add more for large-scale testing
│
└── README.txt                # Project summary, usage instructions.

---

## 📝 WHAT EACH FILE DOES ==>

**search_engine.cpp**
- Loading and indexing all .txt files in the specified folder
- Processing user queries
- Performing fuzzy correction (if needed)
- Ranking and displaying results

**sample1.txt to sample25.txt**
- Sample documents with varied content for search testing.

---

## 🚀 HOW TO RUN ==>

# Step 1: Move to the project directory:
cd "D:\CustomSearchEngine\src"
D:

# Step 2: Build the executable (if not already built):
g++ -std=c++17 -o search_engine.exe main.cpp file_parser.cpp indexer.cpp search_engine.cpp

# Step 3: Run the search engine:
search_engine.exe

---

## ✨ SAMPLE OUTPUT ==>

Enter search query (or type 'exit'): machne

Fuzzy word detected, replaced with "machine"

Ranked Results:
[1] File: ../test_files/sample1.txt    ||    Line: 4    ||    Score: 0.200
Line 4: Machine learning enables computers to learn from data.
🟢 Status: Index successfully created, search completed with fuzzy correction.

---

## 📬 CONTACT ==>

For questions or feedback, feel free to reach out!

---