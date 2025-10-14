/**
 * SearchNewBooks.cpp
 * 
 * Main program for searching new books using different search strategies.
 * Reads book data from files, allows user to select search method (linear,
 * binary, or recursive binary), performs searches, times the search phase,
 * and outputs results.
 */

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include "book.h"
#include "search.h"
#include "Timer.h"

using namespace std;

/**
 * Parse a single line from a book data file into a Book object.
 * 
 * Expected format: isbn,language,type
 * Example: 9780132350884,english,new
 * 
 * @param line The input string containing comma-separated book data
 * @param out Reference to Book object that will be populated with parsed data
 * @return true if parsing succeeded, false if line is malformed or empty
 */
static bool parseBookLine(const string &line, Book &out) {
    // Reject empty lines
    if (line.empty()) return false;
    
    // Find first comma (separates ISBN from language)
    size_t p1 = line.find(',');
    if (p1 == string::npos) return false;
    
    // Find second comma (separates language from type)
    size_t p2 = line.find(',', p1 + 1);
    if (p2 == string::npos) return false;
    
    // Extract the three fields
    string isbnStr = line.substr(0, p1);
    string lang = line.substr(p1 + 1, p2 - p1 - 1);
    string type = line.substr(p2 + 1);
    
    // Convert ISBN string to unsigned integer
    try {
        size_t isbn = std::stoull(isbnStr);
        out = Book(lang, type, isbn);
        return true;
    } catch (...) {
        // Invalid ISBN format (non-numeric or out of range)
        return false;
    }
}

/**
 * Main program entry point.
 * 
 * Usage: SearchNewBooks <newbooks.dat> <requests.dat> [output_file.dat]
 * 
 * Algorithm:
 * 1. Parse command line arguments and validate file access
 * 2. Load all new books from the first file into a vector
 * 3. Sort books using operator< (by ISBN, then type, then language)
 * 4. Prompt user to select a search method (linear/binary/recursive)
 * 5. Preprocess data if needed (sort again for binary searches)
 * 6. Start timer and search for each requested book
 * 7. Stop timer and report elapsed time
 * 8. Write count of found books to output file
 */
int main(int argc, char* argv[]) {
    // ===== Step 1: Validate command line arguments =====
    if (argc < 3) {
        std::cerr << "Usage: program <newbooks.dat> <requests.dat> [result_file.dat]" << std::endl;
        return 1;
    }

    // ===== Step 2: Open and validate input files =====
    ifstream newFile(argv[1]);  // File containing available new books
    ifstream reqFile(argv[2]);  // File containing books to search for
    if (!newFile.is_open()) {
        std::cerr << "Error: cannot open file " << argv[1] << std::endl;
        return 1;
    }
    if (!reqFile.is_open()) {
        std::cerr << "Error: cannot open file " << argv[2] << std::endl;
        return 1;
    }

    // ===== Step 3: Load all books from the new books file =====
    vector<Book> books;
    string line;
    while (std::getline(newFile, line)) {
        Book b;
        if (parseBookLine(line, b)) books.push_back(b);
    }

    // ===== Step 4: Sort books for efficient searching =====
    // Uses Book::operator< which orders by: ISBN -> type -> language
    std::sort(books.begin(), books.end());

    // ===== Step 5: Determine output filename =====
    // Use third argument if provided, otherwise default to "found.dat"
    string outFileName = "found.dat";
    if (argc >= 4) outFileName = argv[3];

    // ===== Step 6: Get search method from user =====
    // l = linear search O(n)
    // b = binary search O(log n)
    // r = recursive binary search O(log n)
    string userInput;
    while (true) {
        cerr << "Choice of search method ([l]inear, [b]inary, [r]ecursiveBinary)? ";
        cin >> userInput;
        if (userInput == "l" || userInput == "b" || userInput == "r") break;
        cerr << "Incorrect choice" << endl;
    }

    // ===== Step 7: Preprocessing - ensure data is sorted for binary searches =====
    size_t found_count = 0;
    // Binary and recursive binary searches require sorted data
    // Sort again to be absolutely certain (belt-and-suspenders approach)
    if (userInput == "b" || userInput == "r") {
        std::sort(books.begin(), books.end());
    }

    // ===== Step 8: START TIMING - measure only the search phase =====
    Timer timer;
    timer.Reset();

    // ===== Step 9: Process each search request =====
    while (std::getline(reqFile, line)) {
        Book req;
        if (!parseBookLine(line, req)) continue;  // Skip malformed lines
        
        bool found = false;
        
        // Dispatch to the appropriate search algorithm
        if (userInput == "l") {
            // Linear search: check every book sequentially
            found = linearSearch(books, req.getLanguage(), req.getType(), req.getISBN());
        } else if (userInput == "b") {
            // Iterative binary search: divide and conquer
            found = binarySearch(books, req.getLanguage(), req.getType(), req.getISBN());
        } else if (userInput == "r") {
            // Recursive binary search: divide and conquer (recursive implementation)
            if (!books.empty()) {
                found = recursiveBinarySearch(books, req.getLanguage(), req.getType(), req.getISBN(), 0, books.size()-1);
            } else {
                found = false;
            }
        }
        
        // Increment counter if book was found in inventory
        if (found) ++found_count;
    }

    // ===== Step 10: STOP TIMING and report performance =====
    double elapsed_us = timer.ElapsedMicroseconds();
    cout << "\n\nCPU time: " << elapsed_us << " microseconds" << endl;

    // ===== Step 11: Write results to output file =====
    ofstream out(outFileName);
    if (!out.is_open()) {
        cerr << "Error: cannot open output file " << outFileName << endl;
        return 1;
    }
    out << found_count << std::endl;  // Write only the count of found books
    out.close();

    return 0;
}