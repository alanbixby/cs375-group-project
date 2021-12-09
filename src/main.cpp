#include <fstream>
#include <iostream>

// Helper Functions
#include "helpers/CLI.h"
#include "helpers/DataStructure.h"
#include "helpers/pdebug.h"

string jsonPath = "./tree-visualizer/treeBuild.json";

using namespace std;

int main([[maybe_unused]] int argc, char* argv[]) {
  // SkipList<string> test;
  // test.insert("5");
  // test.insert("16");
  // test.insert("12");
  // test.remove("16");
  // test.print();
  // exit(1);

  string executable = argv[0];
  DataStructureEnum dsa = RED_BLACK_TREE_INT;
  cout << endl;
  while (true) {
    pdebug_val(dsa);
    switch (dsa) {
      case BINARY_SEARCH_TREE: {
        auto bst = new BST<string>();
        cout << "Initialized an unbalanced BST.\n" << endl;
        while (true) {
          DataStructureEnum temp = NONE;
          temp = CLI::run(bst, executable, jsonPath);
          if (temp && temp != BINARY_SEARCH_TREE) {
            delete bst;
            CLI::clearJson(jsonPath);
            dsa = temp;
            break;
          } else {
            cout << "Already in use!" << endl << endl;
          }
        }
        break;
      }

      case BINARY_SEARCH_TREE_INT: {
        auto bst_int = new BST<int>();
        cout << "Initialized an unbalanced BST [INT].\n" << endl;
        while (true) {
          DataStructureEnum temp = NONE;
          temp = CLI::run(bst_int, executable, jsonPath);
          if (temp && temp != BINARY_SEARCH_TREE_INT) {
            delete bst_int;
            CLI::clearJson(jsonPath);
            dsa = temp;
            break;
          } else {
            cout << "Already in use!" << endl << endl;
          }
        }
        break;
      }

      case RED_BLACK_TREE: {
        auto rbtree = new RedBlackBST<string>();
        cout << "Initialized a balanced Red Black BST.\n" << endl;
        while (true) {
          DataStructureEnum temp = NONE;
          temp = CLI::run(rbtree, executable, jsonPath);
          if (temp && temp != RED_BLACK_TREE) {
            delete rbtree;
            CLI::clearJson(jsonPath);
            dsa = temp;
            break;
          } else {
            cout << "Already in use!" << endl << endl;
          }
        }
        break;
      }

      case RED_BLACK_TREE_INT: {
        auto rbtree_int = new RedBlackBST<int>();
        cout << "Initialized a balanced Red Black BST [INT].\n" << endl;
        while (true) {
          DataStructureEnum temp = NONE;
          temp = CLI::run(rbtree_int, executable, jsonPath);
          if (temp && temp != RED_BLACK_TREE_INT) {
            delete rbtree_int;
            CLI::clearJson(jsonPath);
            dsa = temp;
            break;
          } else {
            cout << "Already in use!" << endl << endl;
          }
        }
        break;
      }

      case SKIP_LIST: {
        SkipList<string>* skiplist = new SkipList<string>();
        cout << "Initialized a SkipList.\n" << endl;
        while (true) {
          DataStructureEnum temp = NONE;
          temp = CLI::run(skiplist, executable, jsonPath);
          if (temp && temp != SKIP_LIST) {
            delete skiplist;
            CLI::clearJson(jsonPath);
            dsa = temp;
            break;
          } else {
            cout << "Already in use!\n" << endl;
          }
        }
        break;
      }

      case SKIP_LIST_INT: {
        SkipList<string>* skiplist = new SkipList<string>(true); // janky solution ftw
        cout << "Initialized a SkipList [INT].\n" << endl;
        while (true) {
          DataStructureEnum temp = NONE;
          temp = CLI::run(skiplist, executable, jsonPath);
          if (temp && temp != SKIP_LIST_INT) {
            delete skiplist;
            CLI::clearJson(jsonPath);
            dsa = temp;
            break;
          } else {
            cout << "Already in use!\n" << endl;
          }
        }
        break;
      }

      case NONE:
        assert(false && "NONE");
    }
  }
}