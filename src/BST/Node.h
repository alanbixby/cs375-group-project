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
  friend ostream& operator<<(ostream& os, const Node<T>& node) {
    os << "{\n";
    bool isInt = typeid(T) == typeid(int);
    if (isInt) {
      os << "  \"type\": \"number\",\n";
    } else {
      os << "  \"type\": \"string\",\n";
    }
    string s = "\"";
    if (node.parent) {
      os << "  \"parent\": " << s << node.parent << s << ",\n";
    }
    if (node.left) {
      os << "  \"left\": " << s << node.left << s << ",\n";
    }
    if (node.right) {
      os << "  \"right\": " << s << node.right << s << ",\n";
    }
    os << "  \"color\": " << s << (node.color ? "BLACK" : "RED") << s << ",\n";
    os << "  \"value\": " << (isInt ? "" : "\"") << node.value
       << (isInt ? "" : "\"") << ",\n";
    os << "  \"id\": " << s << &node << s << "\n";
    os << "}";
    return os;
  }
};

#endif