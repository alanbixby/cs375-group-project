#ifndef ADD_H
#define ADD_H

#include <iostream>
#include <string>

#include "../../RedBlackBST.h"
#include "../Input.h"

using namespace std;

extern RedBlackBST<string> bst;
// extern BST<string> bst;

namespace Add {
  void run(Input* command) {
    cout << endl;
    string value = command->getArg(1);
    if (!value.empty()) {
      bst.insert(value);
      cout << "Added " << value << " to the tree" << endl;
    } else {
      cout << "  error: Invalid command. Usage:" << endl;
      cout << "  error:    insert <value>" << endl;
      cout << "  error:      ↳ add <value> (ALIAS)" << endl;
    }
    cout << endl;
    delete command;
  }
};

#endif