#ifndef RED_BLACK_BST_H
#define RED_BLACK_BST_H

#include <iostream>
#include <queue>

#include "BST.h"

template <class T>
class RedBlackBST : public BST<T> {
 private:
  Node<T>* getParent(Node<T>*);
  Node<T>* getGrandParent(Node<T>*);
  Node<T>* getSibling(Node<T>*);
  void remove(Node<T>*);
  void doubleBlack(Node<T>*);
  void leftRotate(Node<T>*);
  void rightRotate(Node<T>*);

 public:
  RedBlackBST<T>() : BST<T>() {}
  void insert(T);
  void remove(T);
  void print();    // Overrides BST<T>::print()'s inorder print LBL
  void inorder();  // Overrides BST<T>::inorder() with colors enabled.
  void levelByLevel();
  string getBuildString();
};

template <class T>
Node<T>* RedBlackBST<T>::getParent(Node<T>* node) {
  if (node) {
    return node->parent;
  }
  return nullptr;
}

template <class T>
Node<T>* RedBlackBST<T>::getGrandParent(Node<T>* node) {
  return getParent(getParent(node));
}

template <class T>
Node<T>* RedBlackBST<T>::getSibling(Node<T>* node) {
  Node<T>* parent = getParent(node);
  if (parent) {
    if (node == parent->right) {
      return parent->left;
    } else if (node == parent->left) {
      return parent->right;
    }
  }
  return nullptr;
}

template <class T>
void RedBlackBST<T>::leftRotate(Node<T>* node) {
  Node<T>* child = node->right;
  Node<T>* grandchild = child->left;
  node->right = grandchild;
  if (grandchild) {
    grandchild->parent = node;
  }
  Node<T>* parent = getParent(node);
  child->parent = parent;
  if (parent == nullptr) {
    BST<T>::root = child;
  } else if (node == parent->left) {
    parent->left = child;
  } else {
    parent->right = child;
  }
  child->left = node;
  node->parent = child;
}

template <class T>
void RedBlackBST<T>::rightRotate(Node<T>* node) {
  Node<T>* child = node->left;
  Node<T>* grandchild = child->right;
  node->left = grandchild;
  if (grandchild) {
    grandchild->parent = node;
  }
  Node<T>* parent = getParent(node);
  child->parent = parent;
  if (parent == nullptr) {
    BST<T>::root = child;
  } else if (node == parent->right) {
    parent->right = child;
  } else {
    parent->left = child;
  }
  child->right = node;
  node->parent = child;
}

template <class T>
void RedBlackBST<T>::insert(T value) {
  Node<T>* node = BST<T>::insert(value);
  if (node == BST<T>::root) {
    return;
  }
  while (node->parent && node->parent->color == RED) {
    Node<T>* parent = getParent(node);
    Node<T>* grandparent = getGrandParent(node);
    if (parent == grandparent->left) {
      Node<T>* uncle = grandparent->right;
      if (uncle && uncle->color == RED) {
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        node = grandparent;
      } else {
        if (node == parent->right) {
          node = parent;
          leftRotate(node);
        }
        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        rightRotate(node->parent->parent);
      }
    } else {
      Node<T>* uncle = grandparent->left;
      if (uncle && uncle->color == RED) {
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        node = grandparent;
      } else {
        if (node == parent->left) {
          node = parent;
          rightRotate(node);
        }
        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        leftRotate(grandparent);
      }
    }
  }
  BST<T>::root->color = BLACK;
}

template <class T>
void RedBlackBST<T>::remove(T value) {
  remove(BST<T>::find(value));
}

template <class T>
void RedBlackBST<T>::remove(Node<T>* node) {
  pdebug_val(node);
  Node<T>* replacement = BST<T>::remove(node);
  pdebug_val(replacement);
  Node<T>* sibling = getSibling(node);

  if (replacement == nullptr) {
    if (node->color == BLACK)
      doubleBlack(node);
    else {
      if (sibling) {
        sibling->color = RED;
      }
    }
  } else if (node->color == RED || replacement->color == RED) {
    replacement->color = BLACK;
  } else {
    doubleBlack(replacement);
  }
}

template <class T>
void RedBlackBST<T>::doubleBlack(Node<T>* node) {
  if (node == BST<T>::root) {
    return;
  }

  Node<T>* parent = getParent(node);
  Node<T>* sibling = getSibling(node);
  if (sibling != nullptr) {
    Node<T>* rightNephew = sibling->right;
    Node<T>* leftNephew = sibling->left;
    bool redRight = rightNephew && rightNephew->color == RED;
    bool redLeft = leftNephew && leftNephew->color == RED;
    bool leftLeft = redLeft && sibling == parent->left;
    bool rightLeft = redLeft && sibling == parent->right;
    bool rightRight = redRight && sibling == parent->left;
    bool leftRight = redRight && sibling == parent->right;

    if (sibling->color == BLACK) {
      if (leftLeft) {
        leftNephew->color = sibling->color;
        sibling->color = parent->color;
        rightRotate(parent);
        parent->color = BLACK;
      } else if (rightLeft) {
        leftNephew->color = parent->color;
        rightRotate(sibling);
        leftRotate(parent);
        parent->color = BLACK;
      } else if (leftRight) {
        rightNephew->color = parent->color;
        leftRotate(sibling);
        rightRotate(parent);
        parent->color = BLACK;
      } else if (rightRight) {
        rightNephew->color = sibling->color;
        sibling->color = parent->color;
        leftRotate(parent);
        parent->color = BLACK;
      } else {
        sibling->color = RED;
        if (parent->color == BLACK) {
          doubleBlack(parent);
        } else {
          parent->color = BLACK;
        }
      }
    } else {
      parent->color = RED;
      sibling->color = BLACK;
      if (sibling == sibling->parent->right) {
        leftRotate(parent);
      } else {
        rightRotate(parent);
      }
      doubleBlack(node);
    }
  }
};

template <class T>
void RedBlackBST<T>::print() {
  levelByLevel();
}

template <class T>
void RedBlackBST<T>::inorder() {
  BST<T>::inorder(true);
}

template <class T>
void RedBlackBST<T>::levelByLevel() {
  BST<T>::levelByLevel(true);
}

template <class T>
string RedBlackBST<T>::getBuildString() {
  return BST<T>::getBuildString(true);
}

#endif