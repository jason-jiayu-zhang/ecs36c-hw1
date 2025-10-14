/**
 * book.h
 * 
 * Book class definition for representing individual books in inventory.
 * Each book has three attributes: ISBN (unique identifier), language, and type.
 * 
 * The class provides:
 * - Constructors for initialization
 * - Getter methods for accessing private members
 * - Operator overloads for comparison and sorting
 * - Stream output support for debugging and display
 */

// lowercase header to match assignment naming
#ifndef BOOK_H_LOWER
#define BOOK_H_LOWER

#include <string>
#include <ostream>

/**
 * Book - Represents a single book with ISBN, language, and type attributes.
 * 
 * Books are compared and sorted by:
 * 1. ISBN (primary key)
 * 2. Type (secondary: new < used < digital)
 * 3. Language (tertiary: alphabetical)
 */
class Book {
private:
    std::string language;  // Book language (e.g., "english", "french", "spanish")
    std::string type;      // Book condition/format (e.g., "new", "used", "digital")
    size_t isbn;           // International Standard Book Number (unique identifier)

public:
    /**
     * Default constructor - creates a book with empty strings and ISBN of 0.
     */
    Book();
    
    /**
     * Parameterized constructor - creates a book with specified attributes.
     * 
     * @param lang The language of the book
     * @param t The type/condition of the book (new/used/digital)
     * @param i The ISBN number
     */
    Book(const std::string& lang, const std::string& t, size_t i);

    /**
     * Getter methods - provide read-only access to private member variables.
     */
    std::string getLanguage() const;
    std::string getType() const;
    size_t getISBN() const;

    /**
     * Less-than operator for sorting books.
     * 
     * Comparison order:
     * 1. Compare by ISBN (ascending)
     * 2. If ISBNs are equal, compare by type (new < used < digital)
     * 3. If types are also equal, compare by language (alphabetical)
     * 
     * @param other The book to compare with
     * @return true if this book should come before 'other' in sorted order
     */
    bool operator<(const Book& other) const;
    
    /**
     * Equality operator for exact matching.
     * 
     * Two books are equal if and only if all three attributes match:
     * ISBN, type, and language must all be identical.
     * 
     * @param other The book to compare with
     * @return true if all attributes are equal
     */
    bool operator==(const Book& other) const;

    /**
     * Stream output operator for printing/debugging.
     * 
     * Formats book as: "ISBN:<isbn>, Language:<language>, Type:<type>"
     * Example: "ISBN:9780132350884, Language:english, Type:new"
     * 
     * @param os Output stream to write to
     * @param book The book to output
     * @return Reference to the output stream (for chaining)
     */
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
};

#endif // BOOK_H_LOWER
