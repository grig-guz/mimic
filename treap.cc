#include "treap.h"
#include<stdio.h>
#include <iostream>

using namespace std;
Treap::Treap() {
  srand(time(0));
  root = NULL;
}

int Treap::find(const std::string& key) {
  TreapNode* curr = root;
	
  while(curr) {
    if (curr->key == key) {
      return curr->value;
    } else if (curr->key < key) {
      curr = curr->right;
    } else {
      curr = curr->left;
    }
  }
  return -1;
}

void Treap::insert(const std::string& key, int value) {

  if (root == NULL) {
    root = new TreapNode(key, value, rand());
    root->left = NULL;
    root->right = NULL;
    return;
  }

  TreapNode* curr = root;
  TreapNode* newNode = new TreapNode(key, value, rand());
  newNode->left = NULL;
  newNode->right = NULL;
  TreapNode* parent;
	
  while(curr) {
    parent = curr;
    if (curr->key < key) {
      curr = curr->right;
    } else {
      curr = curr->left;
    }
  }
	
  if (parent->key < key) {
    parent->right = newNode;
  } else {
    parent->left = newNode;
  }
  balance(newNode);
} 

void Treap::balance(TreapNode*& newChild) {
  TreapNode* rotor = findParent(newChild);
  TreapNode* parent;
	
  // If child's priority is smaller than its parent's
  while (newChild->priority < rotor->priority) {
    // find parent of rotor to pass it to rotate functions
    parent = findParent(rotor);
		
    // if parent of rotor exists (rotor is not root)
    if (parent) {
      // newChild is rotor's left child
      if (rotor->left && rotor->left->key == newChild->key) {
        // rotor is parent's left child  	
        if (parent->left && parent->left->key == rotor->key) {
          rotateRight(parent->left);

        // rotor is parent's right child
        } else {
          if (parent->right && parent->right->key == rotor->key) {
            rotateRight(parent->right);
          }
        }
			
      // newChild is rotor's right child
      } else {
	// rotor is parent's left child
        if (parent->left && parent->left->key == rotor->key) {
          rotateLeft(parent->left);
        // rotor is parent's right child
        } else {
          if (parent->right && parent->right->key == rotor->key) {
            rotateLeft(parent->right);
          }
        }
      }
    // rotor is root
    } else {
      // if root's left child exists
      if (root->left && root->left->key == newChild->key) {
	// if root's left child is newChild				
        rotateRight(root);				
        return;

      } else {
        // if root's right child is newChild
        if (root->right && root->right->key == newChild->key) {
          rotateLeft(root);				
          return;
        }
      }
    }
    rotor = parent;
  }
}
		
void Treap::rotateRight(TreapNode*& rotor) {

  TreapNode* child = rotor->left;
  rotor->left = child->right;
  child->right = rotor;
  rotor = child;
}

void Treap::rotateLeft(TreapNode*& rotor) {

  TreapNode* child = rotor->right;
  rotor->right = child->left;
  child->left = rotor;
  rotor = child;
}

TreapNode* Treap::findParent(TreapNode* child) {

  if (child->key == root->key) return NULL;
  TreapNode* curr = root;

  while(curr) {
    if (curr->left) {
      if (curr->left->key == child->key) {
        return curr;
      } 
    } 
    if (curr->right) {
      if (curr->right->key == child->key) {
        return curr;
      }
    }
    if (curr->key < child->key) {
      curr = curr->right;
    } else {
      curr = curr->left;			
    }
  }
  return NULL;
}
