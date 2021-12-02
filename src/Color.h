#ifndef COLOR_H
#define COLOR_H

#include <ostream>

using namespace std;

enum Color { RED, BLACK };

inline ostream& operator<<(ostream& os, const Color& color) {
  os << "\033[" << (color ? 39 : 31) << "m";
  return os;
}

#endif