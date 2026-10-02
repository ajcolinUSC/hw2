#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include <set>
#include <string>
#include <vector>

#include "datastore.h"
#include "product.h"
#include "user.h"

class MyDataStore : public DataStore {
public:
  MyDataStore();
  ~MyDataStore();

  void addProduct(Product *p);
  void addUser(User *u);
  std::vector<Product *> search(std::vector<std::string> &terms, int type);
  void dump(std::ostream &ofile);

  bool isValidUser(std::string username);
  void addToCart(std::string username, Product *p);
  void viewCart(std::string username);
  void buyCart(std::string username);

private:
  User *getUser(std::string username);

  std::vector<Product *> products_;
  std::vector<User *> users_;
  std::map<std::string, std::set<Product *> > keywordMap_;
  std::map<std::string, std::vector<Product *> > carts_;
};

#endif
