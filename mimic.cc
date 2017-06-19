#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "treap.h"

using namespace std;

// Replace all characters except letters (A-Z,a-z) in line with ' ',
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
  for( string::iterator it = line.begin(); it != line.end(); ++it ) {
    if( !isalpha(*it) ) {
      if( (*it != '-' && *it != '\'') ||
	  it == line.begin() || it+1 == line.end() ||
	  !isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
	*it = ' ';
      }
    } else {
      *it = tolower(*it);
    }
  }
}

int main(int argc, char *argv[]) {
  if( argc < 2 || argc > 3 ) {
    cerr << "Usage: " << argv[0] << " n book.txt" << endl;
    exit(1);
  }

  int n = atoi(argv[1]);
  
  ifstream fin;
  fin.open(argv[2]);
  if( !fin.is_open() ) {
    cerr << "Unable to open " << argv[1] << endl;
    exit(2);
  }
  Treap treap = Treap();

  string line;
  string word;
  vector<string> words;
  vector<int> all_word_ranks;
  vector<vector<int> > follower_ranks;

  int value;
  int big_r = 0;
  int prev_value = -1;
  while( !fin.eof() ) {
    getline(fin,line);
    lowercaseWords(line);
    istringstream iss(line, istringstream::in);
    while( iss >> word ) {
      value = treap.find(word);
      if (value == -1) {
        treap.insert(word, big_r);
 	words.push_back(word);	
	all_word_ranks.push_back(big_r);
	follower_ranks.push_back(*(new vector<int>));
	if (prev_value != -1) {
	  (follower_ranks[prev_value]).push_back(big_r);
	} else {
	  if (big_r != 0) {
	    (follower_ranks[big_r - 1]).push_back(big_r);	
	  }
	}
	big_r++;
      } else {
	  all_word_ranks.push_back(value);
	
          if (prev_value != -1) {
      	    (follower_ranks[prev_value]).push_back(value);
      	  } else {
	    (follower_ranks[big_r - 1]).push_back(value);
	}
      }
      prev_value = value;
    }
  }
  fin.close();
  if (n == 0) {
    for (unsigned int i = 0; i < words.size(); i++) {
	  cout << words[i] << " : ";
	  for (unsigned int j = 0; j < (follower_ranks[i]).size(); j++) {
	  	  cout << words[(follower_ranks[i])[j]] << " ";
	  }
	  cout << endl;
    }
  } else {
      vector<int> A = all_word_ranks;
      while (n > 0) {
	
	int i = rand() % A.size();
	cout << words[A[i]] << endl;
	if (follower_ranks[A[i]].empty()) {
	  A = all_word_ranks;
	} else {
	  A = follower_ranks[A[i]];
	}
	n--;
      }
  }
  
  return 0;
}
