#ifndef RED_BLACK_BST_H
#define RED_BLACK_BST_H

#include <assert.h>

#include "Color.h"
#include "Node.h"

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

  void rightRotate(Node<T>* Q) {
    assert(Q);
    Node<T>* P = Q->left;
    assert(P);
    Q->left = P->right;
    assert(P->right);
    P->right->parent = Q;
    P->right = Q;
    Q->parent = P;
  }

  void leftRotate(Node<T>* P) {
    assert(P);
    Node<T>* Q = P->right;
    assert(Q);
    P->right = Q->left;
    assert(Q->left);
    Q->left->parent = P;
    Q->left = P;
    P->parent = Q;
  }

 public:
  RedBlackBST<T>() : BST<T>() {}
  Node<T>* insert(T value) {
    pdebug_val(value);
    Node<T>* node = BST<T>::insert(value);
    if (node == BST<T>::root) {
      return node;
    }

    node->color = RED;

    Node<T>* temp = node;
    while (temp && temp != BST<T>::root) {
      Node<T>* parent = getParent(temp);
      assert(parent);  // Must have a parent if temp != root;
      if (parent->color == BLACK) {
        break;
      }

      Node<T>* uncle = getUncle(temp);
      assert(uncle);
      if (uncle->color == RED) {
        parent->color = BLACK;
        uncle->color = BLACK;
        temp = getGrandParent(temp);
      } else {  // uncle->color == BLACK
        Node<T>* grandparent = getGrandParent(temp);
        if (parent == grandparent->left) {
          if (temp == parent->right) {
            // Left Right Case
            // https://media.geeksforgeeks.org/wp-content/cdn-uploads/redBlackCase3b.png
            // Left Rotate parent
            // Apply Left Left Case
            assert(parent == grandparent->left && temp == parent->right);
            leftRotate(parent);
          }
          // Left Left Case
          rightRotate(grandparent);
        } else {
          if (temp == parent->left) {
            // Right Left Case
            // https://media.geeksforgeeks.org/wp-content/cdn-uploads/redBlackCase3d.png
            // Right Rotate parent
            // Apply Right Right Case
            assert(parent == grandparent->right && temp == parent->left);
            rightRotate(parent);
          } else {
            // Right Right Case
            // https://media.geeksforgeeks.org/wp-content/cdn-uploads/redBlackCase3c.png
            // Left Rotate grandparent
            // Swap colors of grandparent and parent
            leftRotate(grandparent);
          }
          Color gColor = grandparent->color;
          grandparent->color = parent->color;
          parent->color = gColor;
        }
        temp = getParent(temp);
      }
    }
    return node;
  }
 
 void remove(Node<T>* node) {
  //BST delete and get replacement node
  Node<T>* replace = BST<T>::remove(node);
  
  //Cannot have double red by property of red-black tree
  assert(!(node->color == RED && replace->color == RED))
  
  Node<T>* sibling = getSibling(node);
  //node is a leaf
  if(replace == nullptr)
  {
    if(node->color == BLACK)
      doubleBlack(node);
    else {
      if(sibling)
        sibling->color = RED; 
    }
    return;
  }
  
  //Simple case of one red
  if(node->color == RED || replace->color == RED) {
    replace->color == BLACK;
    return;
  }
  else {
   doubleBlack(replace);
   return;
  }
 }
 void doubleBlack(Node<T>* node) {
   //no need to fix if node is root
   if(node == root)
    return;
   
   Node<T>* parent = getParent(node);
   Node<T>* sibling = getSibling(node);
 
   if(sibling) {
     bool redRight = (sibling->right != nullptr && sibling->right->color == RED);
     bool redLeft = (sibling->left != nullptr && sibling->left->color == RED);
     bool leftLeft = (redLeft && sibling == sibling->parent->left);
     bool rightLeft = (redLeft && !(sibling == sibling->parent->left));
     bool rightRight = (redRight && !(sibling == sibling->parent->left));
     bool leftRight = (redRight && sibling == sibling->parent->left);
     //cases 3.2a1 - 3.2b on geeksforgeeks https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
     if(sibling->color == BLACK) {
       if(leftLeft) {
         sibling->left->color = sibling->color;
         sibling->color = parent->color;
         rightRotate(parent);
         parent->color = BLACK;
       }
       else if(rightLeft) {
         sibling->left->color = parent->color;
         rightRotate(sibling);
         leftRotate(parent);
         parent->color = BLACK;
       }
       else if(leftRight) {
         sibling->right->color = parent->color;
         leftRotate(sibling);
         rightRotate(parent);
         parent->color = BLACK;
       }
       else if(rightRight) {
         sibling->right->color = sibling->color;
         sibling->color = parent->color;
         leftRotate(parent);
         parent->color = BLACK;
       }
       else {
         sibling->color = RED;
         if(parent->color == BLACK)
           doubleBlack(parent);
         else
           parent->color = BLACK;
       }
     }
     //case 3.3 on geeksforgeeks https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
     else {
       parent->color = RED;
       sibling->color = BLACK;
       if(sibling == sibling->parent->right)
         leftRotate(parent);
       else
         rightRotate(parent);
      
       doubleBlack(node);
     }
     return;
};

#endif
