#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>

#include "Map.h"
#include "../helpers/pdebug.h"

using namespace std;

template <class T>
struct SkipList : public Map<string, string> {
  SkipList<T>() : Map<string, string>(){};
  ~SkipList<T>(){};

  void insert(string value) {
    Map<string, string>::insert({{value}, {value}});
  };

  int getHeight() { return currLevel; };

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

  string getBuildString([[maybe_unused]] bool color = false) {
    stringstream ss;
    for (int i = 0; i <= currLevel; i++) {
      SLNode *node = head->next[i];
      stringstream temp;
      temp << "{ \"level\": " << i << ", \"set\": [";
      bool isEmpty = true;
      while (node != nullptr) {
        if (node->key != nullptr) {
          temp << "\"" << std::get<0>(*(node->key)) << "\", ";
          isEmpty = false;
        }
        node = node->next[i];
      }
      string levelJson = temp.str();
      levelJson = levelJson.substr(0, levelJson.length() - 2) + (isEmpty ? " [" : "") + "] },\n";
      ss << levelJson;
    }

    string output = ss.str();
    output = "[" + output.substr(0, output.length() - 0) + "{ \"style\": \"SkipList\" }]";
    pdebug_val(output);
    return output;
  }
};

#endif