#ifndef EXIT_H
#define EXIT_H

#include <iostream>
#include <string>

#include "../Input.h"

using namespace std;

namespace Exit {
template <template <typename> class D, typename T>
void run(Input* command, D<T>* t) {
  delete command;
  delete t;
  exit(0);
}
};  // namespace Exit

#endif