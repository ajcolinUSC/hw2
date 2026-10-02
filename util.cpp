#include "util.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

using namespace std;
std::string convToLower(std::string src) {
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords) {
  std::set<string> result;
  std::string curr = "";
  for (int i = 0; i < rawWords.size(); ++i) {
    if (!std::isalnum(static_cast<unsigned char>(
            rawWords[i]))) { // not a letter or number
      if (curr.size() >= 2) {
        result.insert(convToLower(curr));
      }
      curr = "";
      continue;
    }
    curr += rawWords[i];
  }
  if (curr.size() >= 2) {
    result.insert(convToLower(curr));
  }
  return result;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from
// http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
  s.erase(s.begin(),
          std::find_if(s.begin(), s.end(),
                       std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end
std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       std::not1(std::ptr_fun<int, int>(std::isspace)))
              .base(),
          s.end());
  return s;
}

// trim from both ends
std::string &trim(std::string &s) { return ltrim(rtrim(s)); }
