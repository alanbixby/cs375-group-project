// TODO: Merge Skiplist In

#ifndef SKIPLIST_H
#define SKIPLIST_H

template <class T>
class SkipList {
 private:
  /* data */
 public:
  SkipList<T>(/* args */){};
  ~SkipList<T>(){};
  void insert(T){};
  void print(){};
  void inorder(){};
  int getHeight(){ return 0; };
  string getBuildString(){ return "[]"; };
  bool find(T){ return false; };
  SkipList<T>* remove(T) { return nullptr; };
};

#endif