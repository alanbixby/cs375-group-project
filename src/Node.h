#ifndef NODE_H
#define NODE_H

#include "Color.h"

template <class T>
struct Node {
  Node<T>* parent = nullptr;
  Node<T>* left = nullptr;
  Node<T>* right = nullptr;
  T value = NULL;
  Color color = BLACK;
  Node<T>(T value) : value(value){};
  Node<T>(T value, Color color) : value(value), color(color){};
  ~Node<T>() {
    if (left) delete left;
    if (right) delete right;
  }
};

#endif