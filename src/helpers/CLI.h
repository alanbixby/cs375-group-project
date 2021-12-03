#ifndef CLI_H
#define CLI_H

#include <chrono>

// DSA Implementations
#include "../BST/BST.h"
#include "../BST/RedBlackBST.h"
#include "../SkipList/SkipList.h"

// Helper Functions
#include "../helpers/CommandPrompt.h"
#include "../helpers/Input.h"

// Commands
#include "../helpers/DataStructure.h"
#include "../helpers/commands/Add.h"
#include "../helpers/commands/Exit.h"
#include "../helpers/commands/Print.h"
#include "../helpers/commands/Remove.h"
#include "../helpers/commands/Use.h"

//Timer for measuring function time
//typedef std::chrono::high_resolution_clock Clock;

namespace CLI {
void clearJson(string writeJson) {
  if (!writeJson.empty()) {
    ofstream treeJson;
    treeJson.open(writeJson);
    pdebug("");
    treeJson << "[{\"disabled\": \"true\"}]";
    treeJson.close();
  }
}

template <template <typename> class D, typename T>
DataStructureEnum run(D<T>* dsa, string executable, string jsonPath = "",
                      bool writeJson = false) {
  while (true) {
    string operation;
    Input* cmd = promptCommand(executable, 2, false);
    operation = cmd->getOperation();
    //auto startTime = Clock::now();
    if (operation == "add") {
      Add::run(cmd, dsa);
    } else if (operation == "remove") {
      Remove::run(cmd, dsa);
    } else if (operation == "print") {
      Print::run(cmd, dsa);
    } else if (operation == "use") {
      DataStructureEnum newDSA = Use::run(cmd);
      if (newDSA != DataStructureEnum::NONE) {
        return newDSA;
      }
    } else if (operation == "exit") {
      clearJson(jsonPath);
      Exit::run(cmd, dsa);
    }
    
    //auto endTime = Clock::now();
    
    //cout << operation << " executed in " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nanoseconds." << endl;
    if (writeJson) {
      pdebug_val(jsonPath);
      ofstream treeJson;
      treeJson.open(jsonPath);
      treeJson << dsa->getBuildString();
      treeJson.close();
    }
  }
}

}  // namespace CLI

#endif
