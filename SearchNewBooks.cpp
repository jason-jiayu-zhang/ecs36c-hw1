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

static bool parseBookLine(const string &line, Book &out) {
    // Expected format: isbn,language,type
    if (line.empty()) return false;
    size_t p1 = line.find(',');
    if (p1 == string::npos) return false;
    size_t p2 = line.find(',', p1 + 1);
    if (p2 == string::npos) return false;
    string isbnStr = line.substr(0, p1);
    string lang = line.substr(p1 + 1, p2 - p1 - 1);
    string type = line.substr(p2 + 1);
    try {
        size_t isbn = std::stoull(isbnStr);
        out = Book(lang, type, isbn);
        return true;
    } catch (...) {
        return false;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: program <newbooks.dat> <requests.dat> [result_file.dat]" << std::endl;
        return 1;
    }

    ifstream newFile(argv[1]);
    ifstream reqFile(argv[2]);
    if (!newFile.is_open()) {
        std::cerr << "Error: cannot open file " << argv[1] << std::endl;
        return 1;
    }
    if (!reqFile.is_open()) {
        std::cerr << "Error: cannot open file " << argv[2] << std::endl;
        return 1;
    }

    vector<Book> books;
    string line;
    while (std::getline(newFile, line)) {
        Book b;
        if (parseBookLine(line, b)) books.push_back(b);
    }

    // sort using overloaded operator<
    std::sort(books.begin(), books.end());

    // accept optional third argument as output filename
    string outFileName = "found.dat";
    if (argc >= 4) outFileName = argv[3];

    string userInput;
    while (true) {
        cerr << "Choice of search method ([l]inear, [b]inary, [r]ecursiveBinary)? ";
        cin >> userInput;
        if (userInput == "l" || userInput == "b" || userInput == "r") break;
        cerr << "Incorrect choice" << endl;
    }

    size_t found_count = 0;
    // For binary/recursive binary searches, ensure the books are sorted per spec
    if (userInput == "b" || userInput == "r") {
        std::sort(books.begin(), books.end());
    }

    Timer timer;
    timer.Reset();

    while (std::getline(reqFile, line)) {
        Book req;
        if (!parseBookLine(line, req)) continue;
        bool found = false;
        if (userInput == "l") {
            found = linearSearch(books, req.getLanguage(), req.getType(), req.getISBN());
        } else if (userInput == "b") {
            found = binarySearch(books, req.getLanguage(), req.getType(), req.getISBN());
        } else if (userInput == "r") {
            if (!books.empty()) {
                found = recursiveBinarySearch(books, req.getLanguage(), req.getType(), req.getISBN(), 0, books.size()-1);
            } else {
                found = false;
            }
        }
        if (found) ++found_count;
    }

    double elapsed_us = timer.ElapsedMicroseconds();
    cout << "\n\nCPU time: " << elapsed_us << " microseconds" << endl;

    // write result to file
    ofstream out(outFileName);
    if (!out.is_open()) {
        cerr << "Error: cannot open output file " << outFileName << endl;
        return 1;
    }
    out << found_count << std::endl;
    out.close();

    return 0;
}