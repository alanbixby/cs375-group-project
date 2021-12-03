// TODO: Merge Skiplist In

#ifndef SKIPLIST_H
#define SKIPLIST_H

template <class T>
class SkipList {
 private:
  /* data */
 public:
  SkipList<T>(){};
  ~SkipList<T>(){};
  void insert(T){};
  void print(){};
  void inorder(){};
  int getHeight() { return 0; };
  string getBuildString() { return "[{\"disabled\": \"true\"}]"; };
  bool find(T) { return false; };
  void remove(T){};
};

#endif