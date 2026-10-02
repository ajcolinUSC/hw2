#include "book.h"
#include "util.h"
#include <iomanip>
#include <sstream>

Book::Book(const std::string name, double price, int qty, std::string isbn,
           std::string author)
    : Product("book", name, price, qty) {
  isbn_ = isbn;
  author_ = author;
}

std::set<std::string> Book::keywords() const {
  std::set<std::string> nameWords = parseStringToWords(name_);
  std::set<std::string> authorWords = parseStringToWords(author_);
  std::set<std::string> all = setUnion(nameWords, authorWords);
  all.insert(convToLower(isbn_));
  return all;
}

std::string Book::displayString() const {
  std::stringstream ss;
  ss << name_ << "\n";
  ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
  ss << std::fixed << std::setprecision(2) << price_ << " " << qty_
     << " left.";
  return ss.str();
}

void Book::dump(std::ostream &os) const {
  Product::dump(os);
  os << isbn_ << "\n" << author_ << std::endl;
}
