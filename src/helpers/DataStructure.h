#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <assert.h>

#include "../BST/BST.h"
#include "../BST/RedBlackBST.h"
#include "../SkipList/SkipList.h"

enum DataStructureEnum {
  NONE,
  BINARY_SEARCH_TREE,
  RED_BLACK_TREE,
  SKIP_LIST,
  BINARY_SEARCH_TREE_INT,
  RED_BLACK_TREE_INT
};

#endif