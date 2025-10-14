/**
 * search.cpp
 * 
 * Implementation of three search algorithms for finding books in a collection.
 * Each algorithm searches for a book with matching ISBN, language, and type.
 * 
 * Algorithms provided:
 * 1. Linear search - simple sequential scan
 * 2. Binary search - iterative divide-and-conquer (requires sorted data)
 * 3. Recursive binary search - recursive divide-and-conquer (requires sorted data)
 */

#include "search.h"

/**
 * Linear search implementation.
 * 
 * Scans through the entire books vector sequentially from start to end.
 * Checks each book to see if all three attributes match the search criteria.
 * 
 * Algorithm:
 * - Iterate through each book in the vector
 * - For each book, check if language, type, AND ISBN all match
 * - Return true immediately when a match is found
 * - Return false if we reach the end without finding a match
 * 
 * Time complexity: O(n) - worst case checks every book
 * Space complexity: O(1) - uses only a constant amount of extra space
 * 
 * @param books Vector of books (can be unsorted)
 * @param lang Target language
 * @param type Target type (new/used/digital)
 * @param isbn Target ISBN number
 * @return true if exact match found, false otherwise
 */
bool linearSearch(const std::vector<Book>& books, const std::string& lang, const std::string& type, size_t isbn) {
    // Scan through every book in sequence
    for (const auto& book : books) {
        // Check if all three attributes match
        if (book.getLanguage() == lang && book.getType() == type && book.getISBN() == isbn) {
            return true;  // Found exact match
        }
    }
    return false;  // No match found after checking all books
}

/**
 * Binary search implementation (iterative).
 * 
 * Uses divide-and-conquer strategy to efficiently search sorted data.
 * Repeatedly divides the search range in half based on ISBN comparison.
 * 
 * IMPORTANT: Assumes the books vector is sorted by operator<
 * (primary: ISBN, secondary: type, tertiary: language)
 * 
 * Algorithm:
 * 1. Start with left = 0, right = size - 1
 * 2. Calculate midpoint
 * 3. Check if midpoint book matches all criteria
 * 4. If ISBN at midpoint < target ISBN, search right half
 * 5. Otherwise, search left half
 * 6. Repeat until match found or search space exhausted
 * 
 * Time complexity: O(log n) - cuts search space in half each iteration
 * Space complexity: O(1) - uses only a few variables
 * 
 * @param books Vector of SORTED books
 * @param lang Target language
 * @param type Target type
 * @param isbn Target ISBN number
 * @return true if exact match found, false otherwise
 */
bool binarySearch(const std::vector<Book>& books, const std::string& lang, const std::string& type, size_t isbn) {
    if (books.empty()) return false;
    
    size_t left = 0;
    size_t right = books.size() - 1;
    
    // Continue searching while there's a valid range
    while (left <= right) {
        // Calculate midpoint (avoids overflow compared to (left+right)/2)
        size_t mid = left + (right - left) / 2;
        const Book &b = books[mid];
        
        // Check if we found an exact match (all three attributes)
        if (b.getISBN() == isbn && b.getLanguage() == lang && b.getType() == type) {
            return true;
        }
        
        // Decide which half to search next based on ISBN comparison
        if (b.getISBN() < isbn) {
            // Target is in the right half
            left = mid + 1;
        } else {
            // Target is in the left half
            if (mid == 0) break; // Avoid underflow on unsigned subtraction
            right = mid - 1;
        }
    }
    
    return false;  // Exhausted search space without finding match
}

/**
 * Recursive binary search implementation.
 * 
 * Recursive version of binary search. Functionally equivalent to the iterative
 * version but uses the call stack instead of a loop.
 * 
 * IMPORTANT: Assumes the books vector is sorted by operator<
 * 
 * Algorithm:
 * 1. Base cases: empty vector or invalid range → return false
 * 2. Calculate midpoint of current search range
 * 3. Check if midpoint matches all criteria → return true
 * 4. If ISBN at midpoint < target: recursively search right half
 * 5. Otherwise: recursively search left half
 * 
 * Time complexity: O(log n) - same as iterative version
 * Space complexity: O(log n) - recursion depth is logarithmic
 * 
 * @param books Vector of SORTED books
 * @param lang Target language
 * @param type Target type
 * @param isbn Target ISBN number
 * @param left Left boundary of current search range (inclusive)
 * @param right Right boundary of current search range (inclusive)
 * @return true if exact match found, false otherwise
 */
bool recursiveBinarySearch(const std::vector<Book>& books, const std::string& lang, const std::string& type, size_t isbn, size_t left, size_t right) {
    // Base case 1: empty vector
    if (books.empty()) return false;
    
    // Base case 2: invalid range (search space exhausted)
    if (left > right) return false;
    
    // Calculate midpoint of current range
    size_t mid = left + (right - left) / 2;
    const Book &b = books[mid];
    
    // Check for exact match at midpoint
    if (b.getISBN() == isbn && b.getLanguage() == lang && b.getType() == type) {
        return true;
    }
    
    // Recursive case 1: search right half
    if (b.getISBN() < isbn) {
        // Ensure we don't go out of bounds
        if (mid + 1 > right) return false;
        return recursiveBinarySearch(books, lang, type, isbn, mid + 1, right);
    }
    
    // Recursive case 2: search left half
    if (mid == 0) return false;  // Avoid underflow
    return recursiveBinarySearch(books, lang, type, isbn, left, mid - 1);
}
