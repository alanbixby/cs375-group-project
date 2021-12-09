#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <sstream>

#include "../helpers/pdebug.h"
#include "Map.h"

using namespace std;

template <class T>
struct SkipList : public Map<string, string> {
  int fakeInt = false;
  SkipList<T>() : Map<string, string>(){};
  SkipList<T>(bool fakeInt) : Map<string, string>(), fakeInt(fakeInt){};
  ~SkipList<T>(){};

  void insert(string value) {
    if (fakeInt) {
      stoi(value);
      value.insert(value.begin(), 11 - value.length(), '0');
    }
    Map<string, string>::insert({{value}, {value}});
  };

  int getHeight() { return currLevel; };

  bool find(string value) {
    try {
      if (fakeInt) {
        stoi(value);
        value.insert(value.begin(), 11 - value.length(), '0');
      }
      auto item = *Map<string, string>::find(value);
      return true;
    } catch (...) {
      return false;
    }
  };

  void remove(string value) {
    if (fakeInt) {
      stoi(value);
      value.insert(value.begin(), 11 - value.length(), '0');
    }
    Map<string, string>::erase(value);
  };

  void print() { levelByLevel(); };

  void inorder() {
    for (auto it = begin(); it != end(); ++it) {
      string output = get<0>(*(it));
      output.erase(0, output.find_first_not_of('0'));
      cout << output << " ";
    }
    cout << endl;
  };

  void levelByLevel() {
    for (int i = 0; i <= currLevel; i++) {
      SLNode *node = head->next[i];
      cout << "Level " << i << ": ";
      while (node != nullptr) {
        if (node->key != nullptr) {
          string output = get<0>(*(node->key));
          output.erase(0, output.find_first_not_of('0'));
          cout << output << " ";
        }
        node = node->next[i];
      }
      cout << endl;
    }
  }

  string getBuildString([[maybe_unused]] bool color = false) {
    stringstream ss;
    for (int i = 0; i <= currLevel; i++) {
      SLNode *node = head->next[i];
      stringstream temp;
      temp << "[";
      while (node != nullptr) {
        if (node->key != nullptr) {
          string output = get<0>(*(node->key));
          output.erase(0, output.find_first_not_of('0'));
          if (fakeInt) {
            temp << output << ", ";
          } else {
            temp << "\"" << output << "\""
                 << ", ";
          }
        }
        node = node->next[i];
      }
      string levelJson = temp.str();
      levelJson = levelJson.substr(0, levelJson.length() - 2) + "],\n";
      ss << levelJson;
    }

    string output = ss.str();
    output = "{ \"data\": [\n" + output.substr(0, output.length() - 2) +
             "\n],\n" + "\"style\": \"SkipList\", \n\"type\": \"" +
             (fakeInt ? "number" : "string") + "\"}";
    pdebug_val(output);
    return output;
  }
};

#endif