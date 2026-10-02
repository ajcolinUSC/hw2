#include "clothing.h"
#include "util.h"
#include <iomanip>
#include <sstream>

Clothing::Clothing(const std::string name, double price, int qty,
                   std::string size, std::string brand)
    : Product("clothing", name, price, qty) {
  size_ = size;
  brand_ = brand;
}

std::set<std::string> Clothing::keywords() const {
  std::set<std::string> nameWords = parseStringToWords(name_);
  std::set<std::string> brandWords = parseStringToWords(brand_);
  std::set<std::string> all = setUnion(nameWords, brandWords);
  return all;
}

std::string Clothing::displayString() const {
  std::stringstream ss;
  ss << name_ << "\n";
  ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
  ss << std::fixed << std::setprecision(2) << price_ << " " << qty_
     << " left.";
  return ss.str();
}

void Clothing::dump(std::ostream &os) const {
  Product::dump(os);
  os << size_ << "\n" << brand_ << std::endl;
}
