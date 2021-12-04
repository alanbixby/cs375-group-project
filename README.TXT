Compile the executable by running "make".

Run "./group-project" to start the executable, by default you will be in a RedBlackBST<int>.

Commands:
  add <value>
  remove <value>
  use bst <?int>
  use rbtree <?int>
  use skiplist
  print
  print height
  print inorder
  exit

The BST structures have an optional int flag that will treat the values as numbers instead of strings, 
this is almostly entirely for aesthetics as when comparing "4" to "100", you'd get 100 < 4, whereas the number version
would parse 100 > 4.

This is important because we have a BST Visualizer that can be run on localhost:3000 by running "node tree-visualizer" (NodeJS required)
Changes made when running the ./group-project executable will be displayed in the HTML page accordingly; for the sake of time, SkipList does
not have an equivalent visualizer.

To make up for this, you can use "print", which does a levelByLevel print of the data structure. For an ordered print (easier to track deletes),
you can use "print inorder".