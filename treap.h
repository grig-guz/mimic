#ifndef __TREAP
#define __TREAP
#include <string>
#include <cstdlib>
#include <string>

struct TreapNode {
  std::string key;
  int value;
  int priority;
  TreapNode* left;
  TreapNode* right;
  // you can add a constructor
  TreapNode(std::string aKey, int aValue, int aPriority) : key(aKey), value(aValue), priority(aPriority), left(NULL), right(NULL) {}
};

class Treap {
  
  // add more helper functions here
  
 public:
  Treap();
  TreapNode *root;
  void insert(const std::string& key, int value);
  int find(const std::string& key);
  void balance(TreapNode*& newNode);
  void rotateRight(TreapNode*& rotor);
  void rotateLeft(TreapNode*& rotor);
  TreapNode* findParent(TreapNode* child);
  // return value for the key if found
  // if not found returns -1
};

#endif
