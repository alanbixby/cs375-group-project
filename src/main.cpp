#include <cassert>
#include <iostream>

#include "BST.h"
#include "RedBlackBST.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[]) {
  RedBlackBST<int> bst;
  // for (int i = 0; i < 20; i++) {
  //   bst.insert(i);
  // }
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
  bst.remove(10);
  bst.print();
  std::cout << std::endl;
  bst.printTree();
}

//    10
// 5      15
//  7    12
// 6 9 11  14
//        13