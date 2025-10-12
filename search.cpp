#include "search.h"

bool linearSearch(const std::vector<Book>& books, const std::string& lang, const std::string& type, size_t isbn) {
    for (const auto& book : books) {
        if (book.getLanguage() == lang && book.getType() == type && book.getISBN() == isbn) {
            return true;
        }
    }
    return false;
}

bool binarySearch(const std::vector<Book>& books, const std::string& lang, const std::string& type, size_t isbn) {
    if (books.empty()) return false;
    size_t left = 0;
    size_t right = books.size() - 1;
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        const Book &b = books[mid];
        if (b.getISBN() == isbn && b.getLanguage() == lang && b.getType() == type) {
            return true;
        }
        if (b.getISBN() < isbn) {
            left = mid + 1;
        } else {
            if (mid == 0) break; // avoid underflow
            right = mid - 1;
        }
    }
    return false;
}

bool recursiveBinarySearch(const std::vector<Book>& books, const std::string& lang, const std::string& type, size_t isbn, size_t left, size_t right) {
    if (books.empty() || left > right) return false;
    size_t mid = left + (right - left) / 2;
    const Book &b = books[mid];
    if (b.getISBN() == isbn && b.getLanguage() == lang && b.getType() == type) return true;
    if (b.getISBN() < isbn) {
        if (mid + 1 > right) return false;
        return recursiveBinarySearch(books, lang, type, isbn, mid + 1, right);
    }
    if (mid == 0) return false;
    return recursiveBinarySearch(books, lang, type, isbn, left, mid - 1);
}
