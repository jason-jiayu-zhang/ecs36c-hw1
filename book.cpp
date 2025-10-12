#include "book.h"
#include <string>

Book::Book() : language(""), type(""), isbn(0) {}

Book::Book(const std::string& lang, const std::string& t, size_t i) : language(lang), type(t), isbn(i) {}

std::string Book::getLanguage() const {
    return language;
}

std::string Book::getType() const {
    return type;
}

size_t Book::getISBN() const {
    return isbn;
}

bool Book::operator<(const Book& other) const {
    if (isbn != other.isbn) return isbn < other.isbn;
    auto rank = [](const std::string &t){
        if (t == "new") return 0;
        if (t == "used") return 1;
        if (t == "digital") return 2;
        return 3; // unknown types go last
    };
    int r1 = rank(type);
    int r2 = rank(other.type);
    if (r1 != r2) return r1 < r2;
    return language < other.language;
}

bool Book::operator==(const Book& other) const {
    return isbn == other.isbn && type == other.type && language == other.language;
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "ISBN:" << book.isbn << ", Language:" << book.language << ", Type:" << book.type;
    return os;
}
