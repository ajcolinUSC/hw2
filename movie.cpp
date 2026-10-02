#include "movie.h"
#include "util.h"
#include <iomanip>
#include <sstream>

Movie::Movie(const std::string name, double price, int qty, std::string genre,
             std::string rating)
    : Product("movie", name, price, qty) {
  genre_ = genre;
  rating_ = rating;
}

std::set<std::string> Movie::keywords() const {
  std::set<std::string> all = parseStringToWords(name_);
  all.insert(convToLower(genre_));
  return all;
}

std::string Movie::displayString() const {
  std::stringstream ss;
  ss << name_ << "\n";
  ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
  ss << std::fixed << std::setprecision(2) << price_ << " " << qty_
     << " left.";
  return ss.str();
}

void Movie::dump(std::ostream &os) const {
  Product::dump(os);
  os << genre_ << "\n" << rating_ << std::endl;
}
