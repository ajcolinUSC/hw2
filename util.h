#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <iterator>
#include <set>
#include <string>

/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T> std::set<T> setUnion(std::set<T> &s1, std::set<T> &s2) {
  std::set<T> result = s1;
  typename std::set<T>::iterator it;
  for (it = s2.begin(); it != s2.end(); ++it) {
    result.insert(*it);
  }

  return result;
}
template <typename T>
std::set<T> setIntersection(std::set<T> &s1, std::set<T> &s2) {
  // create results set
  // iterate through smaller set and check if item in set 1 is in set 2,
  // if so then add it to new set
  // return result set
  std::set<T> result;
  std::set<T> *s;
  std::set<T> *b;
  typename std::set<T>::iterator it;
  if (s1.size() < s2.size()) {
    s = &s1;
    b = &s2;
  } else {
    s = &s2;
    b = &s1;
  }
  for (it = s->begin(); it != s->end(); ++it) {
    if (b->find(*it) != b->end()) { // check if element is in the bigger one
      result.insert(*it);
    }
  }
  return result;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from
// http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s);

// Removes any trailing whitespace
std::string &rtrim(std::string &s);

// Removes leading and trailing whitespace
std::string &trim(std::string &s);
#endif
