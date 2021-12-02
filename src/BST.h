#ifndef BST_H
#define BST_H

#include <iostream>
#include <stack>

#include "Node.h"

template <class T>
class BST {
 protected:
  Node<T>* root = nullptr;
  void remove(Node<T>*);

 public:
  BST<T>(){};
  ~BST<T>();
  Node<T>* insert(T);
  Node<T>* find(T);
  void remove(T);
  Node<T>* getRoot();
  void inorder(bool color = false);
  void print();
};

template <class T>
BST<T>::~BST<T>() {
  if (root) {
    delete root;
  }
}

template <class T>
Node<T>* BST<T>::insert(T value) {
  if (root == nullptr) {
    root = new Node<T>(value, BLACK);
    return root;
  }
  Node<T>* temp = root;
  while (true) {
    if (value <= temp->value) {
      if (temp->left) {
        temp = temp->left;
      } else {
        temp->left = new Node<T>(value, RED);
        temp->left->parent = temp;
        return temp->left;
      }
    } else {
      if (temp->right) {
        temp = temp->right;
      } else {
        temp->right = new Node<T>(value, RED);
        temp->right->parent = temp;
        return temp->right;
      }
    }
  }
}

template <class T>
Node<T>* BST<T>::find(T key) {
  Node<T>* temp = root;
  while (temp) {
    if (key == temp->value) {
      return temp;
    } else if (key < temp->value) {
      temp = temp->left;
    } else {
      temp = temp->right;
    }
  }
  return nullptr;
}

template <class T>
void BST<T>::remove(T value) {
  remove(find(value));
}

template <class T>
void BST<T>::remove(Node<T>* node) {
  // Node does not exist
  if (!node) {
    return;
  }

  Node<T>* parent = node->parent;

  // 0 Children
  if (node->left == nullptr && node->right == nullptr) {
    if (node == root) {
      root = nullptr;
    } else {
      if (node == parent->left) {
        parent->left = nullptr;
      } else {
        parent->right = nullptr;
      }
    }
    delete node;
    return;
  }

  // 2 Children
  if (node->left && node->right) {
    Node<T>* temp = node->right;
    while (temp->left) {
      temp = temp->left;
    }
    node->value = temp->value;
    remove(temp);
    return;
  }

  // 1 Child
  Node<T>* child;
  if (node->left) {
    child = node->left;
  } else {
    child = node->right;
  }

  child->parent = parent;
  if (node == parent->left) {
    parent->left = child;
  } else if (node == parent->right) {
    parent->right = child;
  } else {
    root = child;
  }

  node->left = nullptr;
  node->right = nullptr;

  delete node;
}

template <class T>
Node<T>* BST<T>::getRoot() {
  return root;
}

template <class T>
void BST<T>::inorder(bool color) {  // Optional bool for RBTree
  stack<Node<T>*> stack;
  Node<T>* node = root;

  while (node || !stack.empty()) {
    while (node) {
      stack.push(node);
      node = node->left;
    }

    node = stack.top();
    stack.pop();

    cout << (color ? node->color : Color::BLACK) << node->value << " "
         << Color::BLACK;

    node = node->right;
  }
  cout << endl;
}

template <class T>
void BST<T>::print() {
  inorder();
}

#endif