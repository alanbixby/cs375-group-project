#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <string>

#include "../../BST/BST.h"
#include "../../BST/RedBlackBST.h"
#include "../../SkipList/SkipList.h"
#include "../Input.h"

using namespace std;

namespace Print {
template <template <typename> class D, typename T>
void run(Input* command, D<T>* tree) {
  cout << endl;
  string style = command->getArg(1);
  if (style == "") {
    tree->print();
  } else if (style == "inorder") {
    tree->inorder();
  } else if (style == "height" || style == "h") {
    int height = tree->getHeight();
    cout << height << endl;
  } else if (style == "json") {
    cout << tree->getBuildString() << endl;
  } else {
    cout << "  error: Invalid command. Usage:" << endl;
    cout << "  error:    print" << endl;
    cout << "  error:    print inorder" << endl;
    cout << "  error:    print height" << endl;
  }
  cout << endl;
  delete command;
}
};  // namespace Print

#endif