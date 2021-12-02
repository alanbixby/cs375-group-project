#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <string>

#include "../../RedBlackBST.h"
#include "../Input.h"

using namespace std;

extern RedBlackBST<string> bst;
// extern BST<string> bst;

namespace Print {
  void run(Input* command) {
    cout << endl;
    string style = command->getArg(1);
    if (style == "") {
      bst.print();
    } else if (style == "inorder") {
      bst.inorder();
    } else if (style == "height" || style == "h") {
      int height = bst.getHeight();
      cout << height << endl;
    } else {
      cout << "  error: Invalid command. Usage:" << endl;
      cout << "  error:    print" << endl;
      cout << "  error:    print inorder" << endl;
      cout << "  error:    print height" << endl;
    }
    cout << endl;
    delete command;
  }
};

#endif