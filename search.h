#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <string>
#include "book.h"

// Return true if found, false otherwise. Do not perform I/O here.
bool linearSearch(const std::vector<Book>& books, const std::string& lang, const std::string& type, size_t isbn);
bool binarySearch(const std::vector<Book>& books, const std::string& lang, const std::string& type, size_t isbn);
bool recursiveBinarySearch(const std::vector<Book>& books, const std::string& lang, const std::string& type, size_t isbn, size_t left, size_t right);

#endif // SEARCH_H
