#include <iostream>
#include "misc/pdebug.h"

#include "BST.h"
#include "RedBlackBST.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[]) {
  RedBlackBST <int>bst;
  bst.insert(10);
  bst.insert(15);
  bst.insert(5);
  bst.insert(12);
  bst.insert(14);
  bst.insert(7);
  bst.insert(6);
  bst.insert(9);
  bst.insert(13);
  bst.insert(11);
  bst.print();
  bst.inorder();
  bst.remove(15);
  bst.remove(7);
  std::cout << std::endl;
  bst.print();
  bst.inorder();
}

//    10
// 5      15
//  7    12
// 6 9 11  14
//        13