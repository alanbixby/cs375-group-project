#ifndef REMOVE_H
#define REMOVE_H

#include <iostream>
#include <string>

#include "../../RedBlackBST.h"
#include "../Input.h"

using namespace std;

extern RedBlackBST<string> bst;
// extern BST<string> bst;

namespace Remove {
  void run(Input* command) {
    cout << endl;
    string value = command->getArg(1);
    if (!value.empty()) {
      bool success = (bool)bst.find(value);
      if (success) {
        cout << "Removed " << value << " from the tree" << endl;
      } else {
        cout << "Couldn't find " << value << " in the tree" << endl;
      }
    } else {
      cout << "  error: Invalid command. Usage:" << endl;
      cout << "  error:    remove <value>" << endl;
      cout << "  error:      ↳ delete <value> (ALIAS)" << endl;
    }
    cout << endl;
    delete command;
  }
};

#endif