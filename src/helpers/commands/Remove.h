#ifndef REMOVE_H
#define REMOVE_H

#include <iostream>
#include <string>
#include <type_traits>

#include "../../BST/BST.h"
#include "../../BST/RedBlackBST.h"
#include "../../SkipList/SkipList.h"
#include "../Input.h"

using namespace std;

namespace Remove {
template <template <typename> class D, typename T>
void run(Input* command, D<T>* tree) {
  cout << endl;
  string value = command->getArg(1);
  if (!value.empty()) {
    T key;
    if constexpr (std::is_integral_v<T>) {
      try {
        key = stoi(value);
      } catch (...) {
        cout << "[!] " << value << "is not a number" << endl;
        return;
      }
    } else {
      key = (T)value;
    }
    try {
      tree->remove(key);
      cout << "Removed " << key << endl;
    } catch (...) {
      cout << "Couldn't find " << value << endl;
    }
  } else {
    cout << "  error: Invalid command. Usage:" << endl;
    cout << "  error:    remove <value>" << endl;
    cout << "  error:      ↳ delete <value> (ALIAS)" << endl;
  }
  cout << endl;
  delete command;
}
};  // namespace Remove

#endif