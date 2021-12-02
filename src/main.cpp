#include <iostream>

// DSA Implementations
#include "BST.h"
#include "RedBlackBST.h"

// Helper Functions
#include "misc/CommandPrompt.h"
#include "misc/Input.h"
#include "misc/pdebug.h"

// Commands
#include "misc/commands/Exit.h"
#include "misc/commands/Add.h"
#include "misc/commands/Print.h"
#include "misc/commands/Remove.h"

string executable;
RedBlackBST<string> bst;
// BST<string> bst;

int main([[maybe_unused]] int argc, char* argv[]) {
  executable = argv[0];
  while (true) {
    string operation;
    Input* cmd = promptCommand(2, false);
    operation = cmd->getOperation();
    if (operation == "add") {
      Add::run(cmd);
    } else if (operation == "remove") {
      Remove::run(cmd);
    } else if (operation == "print") {
      Print::run(cmd);
    } else if (operation == "exit") {
      Exit::run(cmd);
      delete cmd;
    }
  }
}

  //    10
  // 5      15
  //  7    12
  // 6 9 11  14
  //        13