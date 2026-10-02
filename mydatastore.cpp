#include "mydatastore.h"
#include "util.h"
#include <iostream>

using namespace std;

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
  for (unsigned int i = 0; i < products_.size(); i++) {
    delete products_[i];
  }
  for (unsigned int i = 0; i < users_.size(); i++) {
    delete users_[i];
  }
}

void MyDataStore::addProduct(Product *p) {
  products_.push_back(p);
  set<string> words = p->keywords();
  set<string>::iterator it;
  for (it = words.begin(); it != words.end(); ++it) {
    keywordMap_[*it].insert(p);
  }
}

void MyDataStore::addUser(User *u) {
  users_.push_back(u);
  carts_[convToLower(u->getName())] = vector<Product *>();
}

vector<Product *> MyDataStore::search(vector<string> &terms, int type) {
  vector<Product *> hits;
  set<Product *> matches;

  if (terms.size() == 0) {
    return hits;
  }

  for (unsigned int i = 0; i < terms.size(); i++) {
    string term = convToLower(terms[i]);
    set<Product *> oneTerm;
    if (keywordMap_.find(term) != keywordMap_.end()) {
      oneTerm = keywordMap_[term];
    }

    if (i == 0) {
      matches = oneTerm;
    } else if (type == 0) {
      matches = setIntersection(matches, oneTerm);
    } else {
      matches = setUnion(matches, oneTerm);
    }
  }

  set<Product *>::iterator it;
  for (it = matches.begin(); it != matches.end(); ++it) {
    hits.push_back(*it);
  }
  return hits;
}

void MyDataStore::dump(ostream &ofile) {
  ofile << "<products>" << endl;
  for (unsigned int i = 0; i < products_.size(); i++) {
    products_[i]->dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile << "<users>" << endl;
  for (unsigned int i = 0; i < users_.size(); i++) {
    users_[i]->dump(ofile);
  }
  ofile << "</users>" << endl;
}

User *MyDataStore::getUser(string username) {
  string lowered = convToLower(username);
  for (unsigned int i = 0; i < users_.size(); i++) {
    if (convToLower(users_[i]->getName()) == lowered) {
      return users_[i];
    }
  }
  return NULL;
}

bool MyDataStore::isValidUser(string username) {
  if (getUser(username) == NULL) {
    return false;
  }
  return true;
}

void MyDataStore::addToCart(string username, Product *p) {
  carts_[convToLower(username)].push_back(p);
}

void MyDataStore::viewCart(string username) {
  vector<Product *> cart = carts_[convToLower(username)];
  int itemNo = 1;
  for (unsigned int i = 0; i < cart.size(); i++) {
    cout << "Item " << itemNo << endl;
    cout << cart[i]->displayString() << endl;
    cout << endl;
    itemNo++;
  }
}

void MyDataStore::buyCart(string username) {
  string key = convToLower(username);
  User *u = getUser(username);
  if (u == NULL) {
    return;
  }

  vector<Product *> cart = carts_[key];
  vector<Product *> stillInCart;
  for (unsigned int i = 0; i < cart.size(); i++) {
    Product *p = cart[i];
    if (p->getQty() > 0 && u->getBalance() >= p->getPrice()) {
      p->subtractQty(1);
      u->deductAmount(p->getPrice());
    } else {
      stillInCart.push_back(p);
    }
  }
  carts_[key] = stillInCart;
}
