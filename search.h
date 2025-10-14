/**
 * search.h
 * 
 * Search strategy interface declarations.
 * Provides three different search algorithms for finding books:
 * - Linear search: O(n) time, no preprocessing required
 * - Binary search: O(log n) time, requires sorted data
 * - Recursive binary search: O(log n) time, recursive implementation
 * 
 * All search functions are pure computation - they do NOT perform any I/O.
 */

#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <string>
#include "book.h"

/**
 * Linear search algorithm.
 * 
 * Searches sequentially through all books in the vector until a match is found
 * or the end is reached. Does not require sorted data.
 * 
 * Time complexity: O(n) where n is the number of books
 * Space complexity: O(1)
 * 
 * @param books Vector of books to search through
 * @param lang Target language to match
 * @param type Target type to match
 * @param isbn Target ISBN to match
 * @return true if a book matching ALL three criteria is found, false otherwise
 */
bool linearSearch(const std::vector<Book>& books, const std::string& lang, const std::string& type, size_t isbn);

/**
 * Iterative binary search algorithm.
 * 
 * Uses divide-and-conquer strategy to efficiently search sorted data.
 * Requires that the books vector is sorted by operator< (ISBN, type, language).
 * 
 * Time complexity: O(log n) where n is the number of books
 * Space complexity: O(1)
 * 
 * @param books Vector of SORTED books to search through
 * @param lang Target language to match
 * @param type Target type to match
 * @param isbn Target ISBN to match
 * @return true if a book matching ALL three criteria is found, false otherwise
 */
bool binarySearch(const std::vector<Book>& books, const std::string& lang, const std::string& type, size_t isbn);

/**
 * Recursive binary search algorithm.
 * 
 * Recursive implementation of binary search using divide-and-conquer.
 * Requires that the books vector is sorted by operator< (ISBN, type, language).
 * 
 * Time complexity: O(log n) where n is the number of books
 * Space complexity: O(log n) due to recursion stack
 * 
 * @param books Vector of SORTED books to search through
 * @param lang Target language to match
 * @param type Target type to match
 * @param isbn Target ISBN to match
 * @param left Left boundary index (inclusive) for current search range
 * @param right Right boundary index (inclusive) for current search range
 * @return true if a book matching ALL three criteria is found, false otherwise
 */
bool recursiveBinarySearch(const std::vector<Book>& books, const std::string& lang, const std::string& type, size_t isbn, size_t left, size_t right);

#endif // SEARCH_H
