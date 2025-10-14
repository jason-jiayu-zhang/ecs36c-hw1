/**
 * book.cpp
 * 
 * Implementation of the Book class methods.
 * Provides concrete implementations for constructors, getters, 
 * operator overloads, and utility functions.
 */

#include "book.h"
#include <string>

// ===== Constructors =====

/**
 * Default constructor - initializes a book with default values.
 * Creates an empty book with ISBN 0.
 */
Book::Book() : language(""), type(""), isbn(0) {}

/**
 * Parameterized constructor - initializes a book with given values.
 * Uses member initializer list for efficiency.
 * 
 * @param lang The language of the book
 * @param t The type/condition (new, used, digital, etc.)
 * @param i The ISBN identifier
 */
Book::Book(const std::string& lang, const std::string& t, size_t i) : language(lang), type(t), isbn(i) {}

// ===== Getter Methods =====

/**
 * Get the language attribute.
 * @return Copy of the language string
 */
std::string Book::getLanguage() const {
    return language;
}

/**
 * Get the type/condition attribute.
 * @return Copy of the type string
 */
std::string Book::getType() const {
    return type;
}

/**
 * Get the ISBN identifier.
 * @return The ISBN number
 */
size_t Book::getISBN() const {
    return isbn;
}

// ===== Operator Overloads =====

/**
 * Less-than comparison operator for sorting.
 * 
 * Implements a three-tier sorting hierarchy:
 * 1. Primary sort by ISBN (ascending)
 * 2. Secondary sort by type using custom ranking:
 *    - "new" books come first (rank 0)
 *    - "used" books come second (rank 1)
 *    - "digital" books come third (rank 2)
 *    - unknown types come last (rank 3)
 * 3. Tertiary sort by language (alphabetical)
 * 
 * @param other The book to compare against
 * @return true if this book should appear before 'other' in sorted order
 */
bool Book::operator<(const Book& other) const {
    // Primary comparison: ISBN
    if (isbn != other.isbn) return isbn < other.isbn;
    
    // Secondary comparison: Type (using custom ranking)
    // Lambda function assigns numeric ranks to type strings
    auto rank = [](const std::string &t){
        if (t == "new") return 0;
        if (t == "used") return 1;
        if (t == "digital") return 2;
        return 3; // unknown types go last
    };
    
    int r1 = rank(type);
    int r2 = rank(other.type);
    if (r1 != r2) return r1 < r2;
    
    // Tertiary comparison: Language (alphabetical)
    return language < other.language;
}

/**
 * Equality comparison operator for exact matching.
 * 
 * Two books are considered equal if and only if ALL three attributes match:
 * - Same ISBN
 * - Same type
 * - Same language
 * 
 * @param other The book to compare against
 * @return true if all attributes are identical
 */
bool Book::operator==(const Book& other) const {
    return isbn == other.isbn && type == other.type && language == other.language;
}

/**
 * Stream insertion operator for output formatting.
 * 
 * Formats book data in a human-readable format:
 * "ISBN:<number>, Language:<lang>, Type:<type>"
 * 
 * Example output: "ISBN:9780132350884, Language:english, Type:new"
 * 
 * @param os The output stream to write to
 * @param book The book object to format
 * @return Reference to the output stream (allows chaining)
 */
std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "ISBN:" << book.isbn << ", Language:" << book.language << ", Type:" << book.type;
    return os;
}
