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
  // void remove(Node<T>*); TODO:
  void leftRotate(Node<T>*);
  void rightRotate(Node<T>*);

 public:
  RedBlackBST<T>() : BST<T>() {}
  void insert(T);
  // void remove(T); TODO:
  void inorder(); // Overrides BST<T>::inorder() with colors enabled.
  void print(); // Overrides BST<T>::print()'s inorder print with level-by-level printing
    
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
void RedBlackBST<T>::inorder() {
  BST<T>::inorder(true);
}

template <class T>
void RedBlackBST<T>::print() {
  if (BST<T>::root == nullptr) {
    return;
  }

  queue<Node<T>*> q;
  q.push(BST<T>::root);

  while (!q.empty()) {
    int count = q.size();
    while (count > 0) {
      Node<T>* node = q.front();
      std::cout << node->color << node->value << " " << Color::BLACK;
      q.pop();
      if (node->left) {
        q.push(node->left);
      }
      if (node->right) {
        q.push(node->right);
      }
      count--;
    }
    std::cout << std::endl;
  }
  std::cout << Color::BLACK;
}

#endif