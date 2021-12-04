#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>

#include "Map.h"

using namespace std;

template <class T>
struct SkipList : public Map<string, string> {
  SkipList<T>() : Map<string, string>(){};
  ~SkipList<T>(){};
  void insert(string value) {
    Map<string, string>::insert({{value}, {value}});
  };
  int getHeight() { return currLevel; };
  string getBuildString() { return "[{\"disabled\": \"true\"}]"; };
  bool find(string value) {
    try {
      auto item = *Map<string, string>::find(value);
      return true;
    } catch (...) {
      return false;
    }
  };
  void remove(string value) {
    try {
      Map<string, string>::erase(value);
    } catch (...) {
      cout << "";
    }
  };
  void print() { levelByLevel(); };
  void inorder() {
    for (auto it = begin(); it != end(); ++it) {
      cout << std::get<0>(*(it)) << " ";
    }
    cout << endl;
  };
  void levelByLevel() {
    for (int i = 0; i <= currLevel; i++) {
      SLNode *node = head->next[i];
      cout << "Level " << i << ": ";
      while (node != nullptr) {
        if (node->key != nullptr) {
          cout << std::get<0>(*(node->key)) << " ";
        }
        node = node->next[i];
      }
      cout << endl;
    }
  }
};

#endif