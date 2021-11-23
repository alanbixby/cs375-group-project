#ifndef RED_BLACK_BST_H
#define RED_BLACK_BST_H

#include <assert.h>

#include "Color.h"
#include "Node.h"

using namespace std;

template <class T>
class RedBlackBST {
 private:
  Node<T>* root = nullptr;

 public:
  RedBlackBST<T>(){};

  Node<T>* getParent(Node<T>* node) {
    if (node) {
      return node->parent;
    }
    return node;
  }

  Node<T>* getGrandParent(Node<T>* node) { return getParent(getParent(node)); }
  Node<T>* getSibling(Node<T>* node) {
    Node<T>* parent = getParent(node);
    // assert(parent);
    if (parent) {
      if (node == parent->right) {
        return parent->left;
      } else {
        return parent->right;
      }
    }
    // TODO: Throw an error or return nullptr?
    return nullptr;
  }
  Node<T>* getUncle(Node<T>* node) {}
};

#endif