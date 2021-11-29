#ifndef RED_BLACK_BST_H
#define RED_BLACK_BST_H

#include <assert.h>

#include "Color.h"
#include "Node.h"

using namespace std;

template <class T>
class RedBlackBST: public BST<T> {
 private:
  Node<T>* root = nullptr;

 public:
  Node<T>* getParent(Node<T>* node) {
    if (node) {
      return node->parent;
    }
    return nullptr;
  }

  Node<T>* getGrandParent(Node<T>* node) { return getParent(getParent(node)); }

  Node<T>* getSibling(Node<T>* node) {
    Node<T>* parent = getParent(node);
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

  Node<T>* getUncle(Node<T>* node) {
    // TODO: Throw an error or return nullptr?
    return getSibling(getParent(node));
  }

  Node<T>* getNearNephew(Node<T>* node) {
    Node<T>* parent = getParent(node);
    Node<T>* sibling = getSibling(node);
    if (sibling) {
      if (node == parent->right) {
        return sibling->right;
      }
      return sibling->left;
    }
    // TODO: Throw an error or return nullptr?
    return nullptr;
  }

  Node<T>* getFarNephew(Node<T>* node) {
    Node<T>* parent = getParent(node);
    Node<T>* sibling = getSibling(node);
    if (sibling) {
      if (node == parent->right) {
        return sibling->left;
      }
      return sibling->right;
    }
    // TODO: Throw an error or return nullptr?
    return nullptr;
  }
};

#endif