#ifndef BST_H
#define BST_H

#include <iostream>
#include <sstream>
#include <queue>
#include <stack>
#include <utility>

#include "Node.h"
#include "misc/pdebug.h"

template <class T>
class BST {
 protected:
  Node<T>* root = nullptr;
  Node<T>* remove(Node<T>*);
  std::pair<std::string, int> getLevelByLevel(bool color = false);

 public:
  BST<T>(){};
  ~BST<T>();
  Node<T>* insert(T);
  Node<T>* find(T);
  void remove(T);
  Node<T>* getRoot();
  void print();
  void inorder(bool color = false);
  void levelByLevel(bool color = false);
  int getHeight();
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
Node<T>* BST<T>::remove(Node<T>* node) {
  // Node does not exist
  if (node == nullptr) {
    return nullptr;
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
    return nullptr;
  }

  // 2 Children
  if (node->left && node->right) {
    Node<T>* temp = node->right;
    while (temp->left) {
      temp = temp->left;
    }
    node->value = temp->value;
    remove(temp);
    return node;
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

  Node<T>* temp = node;
  delete node;
  return temp;
}

template <class T>
Node<T>* BST<T>::getRoot() {
  return root;
}

template <class T>
void BST<T>::print() {
  levelByLevel();
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
std::pair<std::string, int> BST<T>::getLevelByLevel(bool color) {
  std::stringstream ss;
  int height = 0;
  if (root == nullptr) {
    return std::make_pair(ss.str(), height);
  }

  queue<Node<T>*> q;
  q.push(root);

  while (!q.empty()) {
    int count = q.size();
    while (count > 0) {
      Node<T>* node = q.front();
      ss << (color ? node->color : Color::BLACK) << node->value << " "
         << Color::BLACK;
      q.pop();
      if (node->left) {
        q.push(node->left);
      }
      if (node->right) {
        q.push(node->right);
      }
      count--;
    }
    ss << std::endl;
    height++;
  }
  ss << Color::BLACK;
  return std::make_pair(ss.str(), height);
}

template <class T>
void BST<T>::levelByLevel(bool color) {
  auto [str, height] = getLevelByLevel(color);
  cout << str.c_str();
}

template <class T>
int BST<T>::getHeight() {
  auto [str, height] = getLevelByLevel(false);
  return height;
}

#endif