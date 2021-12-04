#ifndef Map_H
#define Map_H

template <class K, class V>
class Map {
  typedef std::pair<const K, V> ValueType;

 public:
  Map() {
    maxLevel = 100;
    currLevel = 0;
    sizeVal = 0;
    head = new SLNode(maxLevel);
    tail = new SLNode(maxLevel);
    head->setSLNodeNext(tail);
    tail->setSLNodePrevious(head);
  }

  Map(const Map &rhs) {
    maxLevel = 100;
    currLevel = 0;
    sizeVal = 0;
    head = new SLNode(maxLevel);
    tail = new SLNode(maxLevel);
    head->setSLNodeNext(tail);
    tail->setSLNodePrevious(head);

    for (auto it = rhs.begin(); it != rhs.end(); ++it) {
      insert(*(it));
    }
  }

  Map &operator=(const Map &rhs) {
    if (this != &rhs) {
      clear();  // Optional?
      for (auto it = rhs.begin(); it != rhs.end(); ++it) {
        insert(*(it));
      }
    }
    return *this;
  }

  Map(std::initializer_list<std::pair<const K, V>> valList) {
    maxLevel = 100;
    currLevel = 0;
    sizeVal = 0;
    head = new SLNode(maxLevel);
    tail = new SLNode(maxLevel);
    head->setSLNodeNext(tail);
    tail->setSLNodePrevious(head);

    for (auto it = valList.begin(); it != valList.end(); it++) {
      insert(*it);
    }
  }

  ~Map() {
    SLNode *temp = head->next[0];
    while (temp->key != nullptr) {
      delete temp->key;
      SLNode *tempDelete = temp;
      temp = temp->next[0];
      delete tempDelete;
    }
    delete head;
    delete tail;
  }

  int randomLevel() {
    bool fiftyPercentChance = (rand() % 2) != 0;
    int newLevel = 0;
    while (fiftyPercentChance && newLevel < maxLevel) {
      newLevel++;
      fiftyPercentChance = (rand() % 2) != 0;
    }
    return newLevel;
  }

  class SLNode {
   public:
    ValueType *key;
    std::vector<SLNode *> next;
    std::vector<SLNode *> previous;

    SLNode() { key = nullptr; }
    explicit SLNode(int level) {
      key = nullptr;
      next.resize(level + 1, nullptr);
      previous.resize(level + 1, nullptr);
    }
    SLNode(const std::pair<const K, V> *newVal, int level) {
      ValueType *retVal = new std::pair<const K, V>(*newVal);
      key = retVal;

      next.resize(level + 1, nullptr);
      previous.resize(level + 1, nullptr);
    }
    void setSLNodeNext(SLNode *node) {
      for (long unsigned int i = 0; i < next.size(); i++) {
        next[i] = node;
      }
    }
    void setSLNodePrevious(SLNode *node) {
      for (long unsigned int i = 0; i < previous.size(); i++) {
        previous[i] = node;
      }
    }
  };

  class Iterator {
   public:
    Iterator() = delete;

    Iterator(const Iterator &rhs) { value = rhs.value; }

    Iterator(SLNode *newIter) { value = newIter; }

    Iterator &operator=(const Iterator &rhs) {
      if (this != &rhs) {
        value = rhs.value;
      }
      return *this;
    }

    Iterator &operator++() {
      value = value->next[0];
      return *this;
    }

    Iterator operator++(int) {
      Iterator retVal = Iterator(value);
      value = value->next[0];
      return retVal;
    }

    Iterator &operator--() {
      value = value->previous[0];
      return *this;
    }

    Iterator operator--(int) {
      Iterator retVal = Iterator(value);
      value = value->previous[0];
      return retVal;
    }

    ValueType &operator*() const { return *(value->key); }

    ValueType *operator->() const { return value->key; }

    SLNode *value;
  };

  class ConstIterator {
   public:
    ConstIterator() = delete;

    ConstIterator(SLNode *newIter) { value = newIter; }

    ConstIterator(const ConstIterator &rhs) { value = rhs.value; }

    ConstIterator(const Iterator &rhs) { value = rhs.value; }

    ConstIterator &operator=(const ConstIterator &rhs) {
      if (this != &rhs) {
        value = rhs.value;
      }
      return *this;
    }

    ConstIterator &operator++() {
      value = value->next[0];
      return *this;
    }

    ConstIterator operator++(int) {
      ConstIterator retVal = ConstIterator(value);
      value = value->next[0];
      return retVal;
    }

    ConstIterator &operator--() {
      value = value->previous[0];
      return *this;
    }

    ConstIterator operator--(int) {
      ConstIterator retVal = ConstIterator(value);
      value = value->previous[0];
      return retVal;
    }

    const ValueType &operator*() const { return *(value->key); }

    const ValueType *operator->() const { return value->key; }

    SLNode *value;
  };

  class ReverseIterator {
   public:
    ReverseIterator() = delete;

    ReverseIterator(const ReverseIterator &rhs) { value = rhs.value; }

    ReverseIterator(SLNode *newIter) {  // Do we need?
      value = newIter;
    }

    ReverseIterator &operator=(const ReverseIterator &rhs) {
      if (this != &rhs) {
        value = rhs.value;
      }
      return *this;
    }

    ReverseIterator &operator++() {
      value = value->previous[0];
      return *this;
    }

    ReverseIterator operator++(int) {
      ReverseIterator retVal = ReverseIterator(value);
      value = value->previous[0];
      return retVal;
    }

    ReverseIterator &operator--() {
      value = value->next[0];
      return *this;
    }

    ReverseIterator operator--(int) {
      ReverseIterator retVal = ReverseIterator(value);
      value = value->next[0];
      return retVal;
    }

    ValueType &operator*() const { return *(value->key); }

    ValueType *operator->() const { return value->key; }

    SLNode *value;
  };

  V &operator[](const K &key) {
    ValueType test = std::pair<const K, V>(key, V());
    std::pair<Iterator, bool> insertTest = insert(test);
    return std::get<1>(*(std::get<0>(insertTest)));
  }

  std::pair<Iterator, bool> insert(const ValueType &newVal) {
    SLNode *current = head;
    K key = std::get<0>(newVal);
    std::vector<SLNode *> update(maxLevel + 1, nullptr);

    for (int i = currLevel; i >= 0; i--) {
      while (current->next[i]->key != nullptr &&
             std::get<0>(*(current->next[i]->key)) < key) {
        current = current->next[i];
      }
      update[i] = current;
    }

    current = current->next[0];

    if (current->key == nullptr || !(std::get<0>(*(current->key)) == key)) {
      int rlevel = randomLevel();

      if (rlevel > currLevel) {
        for (int i = currLevel + 1; i < rlevel + 1; i++) {
          update[i] = head;
        }
        currLevel = rlevel;
      }

      SLNode *n = new SLNode(&newVal, rlevel);

      for (int i = 0; i <= rlevel; i++) {
        n->next[i] = update[i]->next[i];
        n->previous[i] = update[i];
        if (update[i]->next[i] != nullptr) {
          update[i]->next[i]->previous[i] = n;
        }
        update[i]->next[i] = n;
      }

      sizeVal++;
      Iterator retIter(n);
      std::pair<Iterator, bool> retVal = std::make_pair(retIter, true);
      return retVal;
    } else {
      Iterator retIter(current);
      std::pair<Iterator, bool> retVal = std::make_pair(retIter, false);
      return retVal;
    }
  }

  template <typename IT_T>
  void insert(IT_T range_beg, IT_T range_end) {
    auto it = range_beg;
    auto it2 = range_end;
    while (it != it2) {
      insert(*(it));
      ++it;
    }
  }

  Iterator find(const K &key) {
    SLNode *current = head;

    for (int i = currLevel; i >= 0; i--) {
      while (current->next[i]->key != nullptr &&
             std::get<0>(*(current->next[i]->key)) < key) {
        current = current->next[i];
      }
    }

    current = current->next[0];

    if (current->key != nullptr && std::get<0>(*(current->key)) == key) {
      Iterator retVal(current);
      return retVal;
    } else {
      Iterator retVal(tail);
      return retVal;
    }
  }

  ConstIterator find(const K &key) const {
    SLNode *current = head;

    for (int i = currLevel; i >= 0; i--) {
      while (current->next[i]->key != nullptr &&
             std::get<0>(*(current->next[i]->key)) < key) {
        current = current->next[i];
      }
    }

    current = current->next[0];

    if (current->key != nullptr && std::get<0>(*(current->key)) == key) {
      ConstIterator retVal(current);
      return retVal;
    } else {
      ConstIterator retVal(tail);
      return retVal;
    }
  }

  size_t size() const { return sizeVal; }

  bool empty() const {
    if (sizeVal == 0) {
      return true;
    } else {
      return false;
    }
  }

  Iterator begin() {
    Iterator retVal(head->next[0]);
    return retVal;
  }

  Iterator end() {
    Iterator retVal(tail);
    return retVal;
  }

  ConstIterator begin() const {
    ConstIterator retVal(head->next[0]);
    return retVal;
  }

  ConstIterator end() const {
    ConstIterator retVal(tail);
    return retVal;
  }

  ReverseIterator rbegin() {
    ReverseIterator retVal(tail->previous[0]);
    return retVal;
  }

  ReverseIterator rend() {
    ReverseIterator retVal(head);
    return retVal;
  }

  V &at(const K &key) {
    Iterator test = find(key);
    if (test.value->key == nullptr) {
      throw std::out_of_range("Index out of bounds.");
    }
    return std::get<1>(*(test));
  }

  const V &at(const K &key) const {
    ConstIterator iter = find(key);
    if (iter.value->key == nullptr) {
      throw std::out_of_range("Index out of bounds.");
    }
    return std::get<1>(*(iter));
  }

  void erase(Iterator pos) {
    K key = std::get<0>(*(pos));
    SLNode *current = head;
    std::vector<SLNode *> update(maxLevel + 1, nullptr);

    for (int i = currLevel; i >= 0; i--) {
      while (current->next[i]->key != nullptr &&
             std::get<0>(*(current->next[i]->key)) < key) {
        current = current->next[i];
      }
      update[i] = current;
    }

    current = current->next[0];

    if (current->key != nullptr && std::get<0>(*(current->key)) == key) {
      for (int i = 0; i <= currLevel; i++) {
        if (update[i]->next[i] != current) break;

        update[i]->next[i] = current->next[i];
        if (current->next[i] != nullptr) {
          current->next[i]->previous[i] = update[i];
        }
      }

      delete current->key;
      delete current;

      while (currLevel > 0 && head->next[currLevel] == 0) {
        currLevel--;
      }
      sizeVal--;
    } else {
      throw std::out_of_range("Key not found.");
    }
  }

  void erase(const K &key) {
    Iterator iter = find(key);
    if (iter.value->key == nullptr) {
      throw std::out_of_range("Key not found.");
    } else {
      erase(iter);
    }
  }

  void clear() {
    SLNode *current = head->next[0];
    while (current->key != nullptr) {
      SLNode *temp = current->next[0];
      erase(std::get<0>(*(current->key)));
      current = temp;
    }
  }

  friend bool operator==(const Iterator &lhs, const Iterator &rhs) {
    return lhs.value == rhs.value;
  }

  friend bool operator==(const ConstIterator &lhs, const ConstIterator &rhs) {
    return lhs.value == rhs.value;
  }

  friend bool operator==(const Iterator &lhs, const ConstIterator &rhs) {
    return lhs.value == rhs.value;
  }

  friend bool operator==(const ConstIterator &lhs, const Iterator &rhs) {
    return lhs.value == rhs.value;
  }

  friend bool operator!=(const Iterator &lhs, const Iterator &rhs) {
    return lhs.value != rhs.value;
  }

  friend bool operator!=(const ConstIterator &lhs, const ConstIterator &rhs) {
    return lhs.value != rhs.value;
  }

  friend bool operator!=(const Iterator &lhs, const ConstIterator &rhs) {
    return lhs.value != rhs.value;
  }

  friend bool operator!=(const ConstIterator &lhs, const Iterator &rhs) {
    return lhs.value != rhs.value;
  }

  friend bool operator==(const ReverseIterator &lhs,
                         const ReverseIterator &rhs) {
    return lhs.value == rhs.value;
  }

  friend bool operator!=(const ReverseIterator &lhs,
                         const ReverseIterator &rhs) {
    return lhs.value != rhs.value;
  }

  friend bool operator==(const Map &lhs, const Map &rhs) {
    if (lhs.size() == rhs.size()) {
      auto itl = lhs.begin();
      auto itr = rhs.begin();
      while (itl != lhs.end()) {
        if (!(std::get<0>(*(itl)) == std::get<0>(*(itr))) ||
            !(std::get<1>(*(itl)) == std::get<1>(*(itr)))) {
          return false;
        }
        ++itl;
        ++itr;
      }
      return true;
    }
    return false;
  }

  friend bool operator!=(const Map &lhs, const Map &rhs) {
    if (lhs == rhs) {
      return false;
    } else {
      return true;
    }
  }

  friend bool operator<(const Map &lhs, const Map &rhs) {
    if (lhs.size() == rhs.size()) {
      auto itr = rhs.begin();
      for (auto itl = lhs.begin(); itl != lhs.end(); ++itl) {
        if (*(itl) < *(itr)) {
          return true;
        }
        if (*(itl) > *(itr)) {
          return false;
        }
        ++itr;
      }
      return false;
    } else if (lhs.size() < rhs.size()) {
      auto itr = rhs.begin();
      for (auto itl = lhs.begin(); itl != lhs.end(); ++itl) {
        if (*(itl) < *(itr)) {
          return true;
        }
        if (*(itl) > *(itr)) {
          return false;
        }
        ++itr;
      }
      return true;
    } else {  // lhs.size() > rhs.size()
      auto itl = lhs.begin();
      for (auto itr = rhs.begin(); itr != rhs.end(); ++itr) {
        if (*(itl) < *(itr)) {
          return true;
        }
        if (*(itl) > *(itr)) {
          return false;
        }
        ++itl;
      }
      return false;
    }
  }

 protected:
  size_t sizeVal;
  int maxLevel;
  int currLevel;
  SLNode *head;
  SLNode *tail;
};

#endif  // Map_H