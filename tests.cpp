#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include "book.h"
#include "search.h"

using std::vector;

int count_matches_linear(const vector<Book>& newbooks, const vector<Book>& requests) {
    int cnt = 0;
    for (const auto &r : requests) {
        if (linearSearch(newbooks, r.getLanguage(), r.getType(), r.getISBN())) ++cnt;
    }
    std::cout << "Linear search found " << cnt << " matches." << std::endl;
    return cnt;
}

int count_matches_binary(vector<Book> newbooks, const vector<Book>& requests) {
    std::sort(newbooks.begin(), newbooks.end());
    int cnt = 0;
    for (const auto &r : requests) {
        if (binarySearch(newbooks, r.getLanguage(), r.getType(), r.getISBN())) ++cnt;
    }
    std::cout << "Binary search found " << cnt << " matches." << std::endl;
    return cnt;
}

int count_matches_recursive_binary(vector<Book> newbooks, const vector<Book>& requests) {
    std::sort(newbooks.begin(), newbooks.end());
    int cnt = 0;
    for (const auto &r : requests) {
        if (!newbooks.empty() && recursiveBinarySearch(newbooks, r.getLanguage(), r.getType(), r.getISBN(), 0, newbooks.size()-1)) ++cnt;
    }
    std::cout << "Recursive binary search found " << cnt << " matches." << std::endl;
    return cnt;
}

void test_all_hit() {
    vector<Book> newbooks = { Book("english","new",123) };
    vector<Book> requests = { Book("english","new",123) };
    assert(count_matches_linear(newbooks, requests) == 1);
    assert(count_matches_binary(newbooks, requests) == 1);
    assert(count_matches_recursive_binary(newbooks, requests) == 1);
    std::cout << "All hit tests passed!" << std::endl;
}

void test_all_miss() {
    vector<Book> newbooks = { Book("english","new",123) };
    vector<Book> requests = { Book("english","new",124) };
    assert(count_matches_linear(newbooks, requests) == 0);
    assert(count_matches_binary(newbooks, requests) == 0);
    assert(count_matches_recursive_binary(newbooks, requests) == 0);
    std::cout << "All miss tests passed!" << std::endl;
}

void test_empty_input() {
    vector<Book> newbooks;
    vector<Book> requests;
    assert(count_matches_linear(newbooks, requests) == 0);
    assert(count_matches_binary(newbooks, requests) == 0);
    assert(count_matches_recursive_binary(newbooks, requests) == 0);
    std::cout << "Empty input tests passed!" << std::endl;
}

void test_duplicate_newbooks() {
    vector<Book> newbooks = { Book("english","new",123), Book("english","new",123) };
    vector<Book> requests = { Book("english","new",123) };
    assert(count_matches_linear(newbooks, requests) == 1);
    assert(count_matches_binary(newbooks, requests) == 1);
    assert(count_matches_recursive_binary(newbooks, requests) == 1);
    std::cout << "Duplicate newbooks tests passed!" << std::endl;
}

void test_type_mismatch() {
    vector<Book> newbooks = { Book("english","new",123) };
    vector<Book> requests = { Book("english","used",123) };
    assert(count_matches_linear(newbooks, requests) == 0);
    assert(count_matches_binary(newbooks, requests) == 0);
    assert(count_matches_recursive_binary(newbooks, requests) == 0);
    std::cout << "Type mismatch tests passed!" << std::endl;
}

void test_language_mismatch() {
    vector<Book> newbooks = { Book("english","new",123) };
    vector<Book> requests = { Book("french","new",123) };
    assert(count_matches_linear(newbooks, requests) == 0);
    assert(count_matches_binary(newbooks, requests) == 0);
    assert(count_matches_recursive_binary(newbooks, requests) == 0);
    std::cout << "Language mismatch tests passed!" << std::endl;
}

void test_book_comparators() {
    Book b1("english", "new", 100);
    Book b2("english", "used", 100);
    Book b3("french", "new", 100);
    Book b4("english", "new", 101);
    assert(b1 < b2); // new < used
    assert(b1 < b3); // english < french
    assert(b1 < b4); // 100 < 101
    assert(b1 == Book("english", "new", 100));
    std::cout << "Book comparator tests passed!" << std::endl;
}

int main() {
    test_all_hit();
    test_all_miss();
    test_empty_input();
    test_duplicate_newbooks();
    test_type_mismatch();
    test_language_mismatch();
    test_book_comparators();
    std::cout << "All unit tests passed!" << std::endl;
    return 0;
}
