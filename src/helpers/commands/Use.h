#ifndef USE_H
#define USE_H

#include <iostream>
#include <string>

#include "../DataStructure.h"
#include "../Input.h"

using namespace std;

namespace Use {
DataStructureEnum run(Input* command) {
  cout << endl;
  string structure = command->getArg(1);
  string type = command->getArg(2);
  pdebug_val(type);
  if (structure == "bst" || structure == "binary" ||
      structure == "unbalanced") {
    if (type == "number" || type == "int") {
      pdebug_val(type);
      return BINARY_SEARCH_TREE_INT;
    }
    return BINARY_SEARCH_TREE;
  } else if (structure == "rbtree" || structure == "red" ||
             structure == "balanced") {
    if (type == "number" || type == "int") {
      return RED_BLACK_TREE_INT;
    }
    return RED_BLACK_TREE;
  } else if (structure == "skiplist" || structure == "skip") {
    if (type == "number" || type == "int") {
      return SKIP_LIST_INT;
    }
    return SKIP_LIST;
  } else {
    cout << "  error: Invalid command. Usage:" << endl;
    cout << "  error:    use bst <?int>" << endl;
    cout << "  error:    use rbtree <?int>" << endl;
    cout << "  error:    use skiplist" << endl;
  }
  cout << endl;
  delete command;
  return DataStructureEnum::NONE;
}
};  // namespace Use

#endif