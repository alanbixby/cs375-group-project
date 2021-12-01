#ifndef BST_H
#define BST_H

#include "Node.h"
#include "pdebug.h"

enum Direction { NIL, LEFT, RIGHT };

template <class T>
class BST {
 protected:
  Node<T>* root = nullptr;

  void print(Node<T>* node) {
    if (node == nullptr) {
      return;
    }

    if (node->left) {
      print(node->left);
    }

    std::cout << node->value << " (" <<  node->color << ")" <<", ";

    if (node->right) {
      print(node->right);
    }
  };

 public:
  BST<T>(){};
  ~BST<T>() {
    if (root) {
      delete root;
    }
  };

  // Non-void return, and colored insert for RedBlackBST usage.
  Node<T>* insert(T value) {
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

  Node<T>* find(T key) {
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

  void remove(T value) { remove(find(value)); }

  void remove(Node<T>* node) {
    // Node does not exist
    if (!node) {
      return;
    }

    Direction direction = NIL;
    Node<T>* parent = node->parent;
    if (parent) {
      if (parent->left == node) {
        direction = LEFT;
      } else {
        direction = RIGHT;
      }
    }

    // 0 Children
    if (node->left == nullptr && node->right == nullptr) {
      pdebug("0 children");
      if (node == root) {
        root = nullptr;
      } else {
        if (direction == LEFT) {
          parent->left = nullptr;
        } else if (direction == RIGHT) {
          parent->right = nullptr;
        }
      }
      delete node;
      return;
    }

    // 2 Children
    if (node->left && node->right) {
      pdebug("2 children");
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
      pdebug("1 child, left");
    } else {
      child = node->right;
      pdebug("1 child, right");
    }

    child->parent = parent;
    if (direction == LEFT) {
      parent->left = child;
    } else if (direction == RIGHT) {
      parent->right = child;
    } else {
      root = child;
    }

    node->left = nullptr;
    node->right = nullptr;

    delete node;
  }

  void print() {
    print(root);
    std::cout << std::endl;
  }
};

#endif