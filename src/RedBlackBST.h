#ifndef RED_BLACK_BST_H
#define RED_BLACK_BST_H

#include <assert.h>

#include <iostream>
#include <queue>

#include "Color.h"
#include "Node.h"

using namespace std;

template <class T>
class RedBlackBST : public BST<T> {
 private:
  Node<T>* getParent(Node<T>* node) {
    if (node) {
      return node->parent;
    }
    return nullptr;
  }

  Node<T>* getGrandParent(Node<T>* node) { return getParent(getParent(node)); }

  Node<T>* getSibling(Node<T>* node) {
    Node<T>* parent = getParent(node);
    if (parent) {
      if (node == parent->right) {
        return parent->left;
      } else {
        return parent->right;
      }
    }
    return nullptr;
  }

  Node<T>* getUncle(Node<T>* node) { return getSibling(getParent(node)); }

  Node<T>* getNearNephew(Node<T>* node) {
    Node<T>* parent = getParent(node);
    Node<T>* sibling = getSibling(node);
    if (sibling) {
      if (node == parent->right) {
        return sibling->right;
      }
      return sibling->left;
    }
    return nullptr;
  }

  Node<T>* getFarNephew(Node<T>* node) {
    Node<T>* parent = getParent(node);
    Node<T>* sibling = getSibling(node);
    if (sibling) {
      if (node == parent->right) {
        return sibling->left;
      }
      return sibling->right;
    }
    return nullptr;
  }

  void leftRotate(Node<T>* x) {
    Node<T>* y = x->right;
    x->right = y->left;
    if (y->left) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      BST<T>::root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;

    // pdebug("leftRotate");
    // assert(node);
    // Node<T>* child = node->right;
    // assert(child);
    // if (child->left) {
    //   child->left->parent = node;
    // }
    // Node<T>* parent = getParent(node);
    // child->parent = parent;
    // if (parent == nullptr) {
    //   BST<T>::root = child;
    // } else if (node == parent->left) {
    //   parent->left = child;
    // } else {
    //   parent->right = child;
    // }
    // child->left = node;
    // node->parent = child;
  }

  void rightRotate(Node<T>* x) {
    assert(x);
    Node<T>* y = x->left;
    assert(y);
    x->left = y->right;
    if (y->right) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      BST<T>::root = y;
    } else if (x == x->parent->right) {
      assert(x->parent);
      x->parent->right = y;
    } else {
      assert(x->parent);
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;

    // pdebug("rightRotate");
    // assert(node);
    // Node<T>* child = node->left;
    // assert(child);
    // if (child->right) {
    //   child->right->parent = node;
    // }
    // child->parent = node->parent;
    // if (node->parent == nullptr) {
    //   BST<T>::root = child;
    // } else if (node == node->parent->left) {
    //   node->parent->left = child;
    // } else {
    //   node->parent->right = child;
    // }
    // child->right = node;
    // node->parent = child;
  }

 public:
  RedBlackBST<T>() : BST<T>() {}
  Node<T>* insert(T value) {
    printTree();
    cout << "inserting " << value << endl;
    printTree();
    cout << endl;
    pdebug("");
    Node<T>* node = BST<T>::insert(value);
    assert(node);
    if (node == BST<T>::root) {
      return node;
    }
    Node<T>* z = node;
    assert(z);
    while (z && z->parent && z->parent->color == RED) {
      pdebug("while loop");
      assert(z->parent);
      assert(z->parent->parent);
      if (z->parent == z->parent->parent->left) {
        pdebug("case1");
        Node<T>* y = z->parent->parent->right;
        if (y && y->color == RED) {
          pdebug("case1a");
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          pdebug("case1b");
          if (z == z->parent->right) {
            z = z->parent;
            leftRotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          rightRotate(z->parent->parent);
        }
      } else {
        pdebug("case2");
        Node<T>* y = z->parent->parent->left;
        if (y && y->color == RED) {
          pdebug("case2a");
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          pdebug("case2b");
          if (z == z->parent->left) {
            z = z->parent;
            rightRotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          leftRotate(z->parent->parent);
        }
      }
    }
    pdebug("exiting while loop");
    assert(BST<T>::root);
    BST<T>::root->color = BLACK;
    return node;

    // Fix-up Function
    // assert(getParent(node));
    // while (getParent(node)->color == RED) {
    //   Node<T>* parent = getParent(node);
    //   Node<T>* grandparent = getGrandParent(node);
    //   assert(grandparent);
    //   if (parent == grandparent->left) {
    //     Node<T>* uncle = grandparent->right;
    //     assert(uncle);
    //     if (uncle->color == RED) {
    //       parent->color = BLACK;
    //       uncle->color = BLACK;
    //       grandparent->color = RED;
    //       node = grandparent;
    //     } else {
    //       if (node == parent->right) {
    //         node = parent;
    //         leftRotate(node);
    //       }
    //       rightRotate(getGrandParent(node));
    //     }
    //   } else {
    //     Node<T>* uncle = grandparent->left;
    //     assert(uncle);
    //     if (uncle->color == RED) {
    //       parent->color = BLACK;
    //       uncle->color = BLACK;
    //       grandparent->color = RED;
    //       node = grandparent;
    //     } else {
    //       if (node == parent->left) {
    //         node = parent;
    //         rightRotate(node);
    //       }
    //       leftRotate(getGrandParent(node));
    //     }
    //   }
    //   BST<T>::root->color = BLACK;
    // if (parent == grandparent->left) {
    //   Node<T>* uncle = grandparent->right;
    //   if (!uncle) {
    //     break;
    //   }
    //   assert(uncle);
    //   if (uncle->color == RED) {
    //     parent->color = BLACK;
    //     uncle->color = BLACK;
    //     grandparent->color = RED;
    //     node = grandparent;
    //   } else {
    //     if (node == parent->right) {
    //       node = parent;
    //       // update relatives due to node's change
    //       parent = getParent(node);
    //       grandparent = getGrandParent(node);
    //       leftRotate(node);
    //     }
    //     parent->color = BLACK;
    //     grandparent->color = RED;
    //     rightRotate(grandparent);
    //   }
    // } else {
    //   Node<T>* uncle = grandparent->left;
    //   if (!uncle) {
    //     break;
    //   }
    //   assert(uncle);
    //   if (uncle->color == RED) {
    //     parent->color = BLACK;
    //     uncle->color = BLACK;
    //     grandparent->color = RED;
    //     node = grandparent;
    //   } else {
    //     if (node == parent->left) {
    //       node = parent;
    //       // update relatives due to node's change
    //       parent = getParent(node);
    //       grandparent = getGrandParent(node);
    //       rightRotate(node);
    //     }
    //     parent->color = BLACK;
    //     grandparent->color = RED;
    //     leftRotate(grandparent);
    //   }
    // }
  }

  void printTree() {
    if (BST<T>::root == nullptr) {
      return;
    }

    queue<Node<T>*> q;
    q.push(BST<T>::root);

    while (!q.empty()) {
      int count = q.size();
      while (count > 0) {
        Node<T>* node = q.front();
        cout << "\033[" << (node->color ? 39 : 31) << "m" << node->value << " ";
        q.pop();
        if (node->left) {
          q.push(node->left);
        }
        if (node->right) {
          q.push(node->right);
        }
        count--;
      }
      cout << endl;
    }
    cout << "\033[39m" << endl;
  }
};

#endif