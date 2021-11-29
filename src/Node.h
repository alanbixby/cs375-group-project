#ifndef NODE_H
#define NODE_H

#include "Color.h"

template <class T>
struct Node {
  Color color = BLACK;
  Node<T>* parent = nullptr;
  Node<T>* left = nullptr;
  Node<T>* right = nullptr;
  T value = NULL;
  Node<T>(T value) : value(value){};
  ~Node<T>() {
    if (left) {
      delete left;
    }
    if (right) {
      delete right;
    }
  }
};

#endif