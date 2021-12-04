#ifndef ADD_H
#define ADD_H

#include <iostream>
#include <string>
#include <type_traits>

#include "../../BST/BST.h"
#include "../../BST/RedBlackBST.h"
#include "../../SkipList/SkipList.h"
#include "../Input.h"

using namespace std;

namespace Add {
template <template <typename> class D, typename T>
void run(Input* command, D<T> *tree) {
  cout << endl;
  string value = command->getArg(1);
  if (!value.empty()) {
    if constexpr (std::is_integral_v<T>) {
      try {
        int i = stoi(value);
        tree->insert(i);
        cout << "Added " << i << endl;
      } catch (...) {
        cout << "[!] " << value << " is not a number" << endl;
      }
    } else {
      tree->insert(value);
      cout << "Added " << value << endl;
    }
  } else {
    cout << "  error: Invalid command. Usage:" << endl;
    cout << "  error:    insert <value>" << endl;
    cout << "  error:      ↳ add <value> (ALIAS)" << endl;
  }
  cout << endl;
  delete command;
}
};  // namespace Add

#endif