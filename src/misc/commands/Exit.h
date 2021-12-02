#ifndef EXIT_H
#define EXIT_H

#include <iostream>
#include <string>

#include "../Input.h"

using namespace std;

namespace Exit {
  void run(Input* command) {
    delete command;
    exit(0);
  }
};

#endif