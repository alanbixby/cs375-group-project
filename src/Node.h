#ifndef NODE_H
#define NODE_H

#include "Color.h"
#include "RedBlackBST.h"

template <class T>
struct Node {
  Color color = BLACK;
  Node<T>* parent = nullptr;
  Node<T>* left = nullptr;
  Node<T>* right = nullptr;
  T key = NULL;
  Node<T>(T key) : key(key){};
};

#endif