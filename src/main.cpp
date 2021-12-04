#include <fstream>
#include <iostream>
#include <variant>

// Helper Functions
#include "helpers/CLI.h"
#include "helpers/DataStructure.h"
#include "helpers/pdebug.h"

string jsonPath = "./tree-visualizer/treeBuild.json";

using namespace std;

int main([[maybe_unused]] int argc, char* argv[]) {
  // stringstream ss;
  // RedBlackBST<int> bst;
  // int count = 0;
  // for (int i = 0; i < 25000; i++) {
  //   bst.insert(i);
  //   ss << ++count << ", " << bst.getHeight() << ", " << i << endl;
  // }

  // ofstream test;
  // test.open("tests/rbbst-increasing.csv");
  // test << ss.str();
  // test.close();
  // exit(0);

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
          temp = CLI::run(bst, executable, jsonPath, true);
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
          temp = CLI::run(bst_int, executable, jsonPath, true);
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
          temp = CLI::run(rbtree, executable, jsonPath, true);
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
          temp = CLI::run(rbtree_int, executable, jsonPath, true);
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
            dsa = temp;
            break;
          } else {
            cout << "Already in use!\n" << endl;
          }
        }
        break;
      }

        // case SKIP_LIST_INT: {
        //   SkipList<int, int>* skiplist_int = new SkipList<int, int>();
        //   cout << "Initialized a SkipList [INT].\n" << endl;
        //   while (true) {
        //     DataStructureEnum temp = NONE;
        //     temp = CLI::run(skiplist_int, executable, jsonPath);
        //     if (temp && temp != SKIP_LIST_INT) {
        //       delete skiplist_int;
        //       dsa = temp;
        //       break;
        //     } else {
        //       cout << "Already in use!" << endl << endl;
        //     }
        //   }
        //   break;
        // }

      case NONE:
        assert(false && "NONE");
    }
  }
}