// lowercase header to match assignment naming
#ifndef BOOK_H_LOWER
#define BOOK_H_LOWER

#include <string>
#include <ostream>

class Book {
private:
    std::string language;
    std::string type;
    size_t isbn;

public:
    Book();
    Book(const std::string& lang, const std::string& t, size_t i);

    std::string getLanguage() const;
    std::string getType() const;
    size_t getISBN() const;

    bool operator<(const Book& other) const;
    bool operator==(const Book& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Book& book);
};

#endif // BOOK_H_LOWER
