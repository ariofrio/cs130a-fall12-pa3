#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class graph {
public:
  struct node {
    string label;
    vector<node*> outgoing;
    
    node(const string& label) : label(label) {}
  };

  node* find(const string& label);
  node* insert(const string& label);

  bool connect(node* p, node* q);
  bool connect(const string& p, const string& q) {
    return connect(find(p), find(q));
  }

  int minimum_hops(node* p, node* q);
  int minimum_hops(const string& p, const string& q) {
    return minimum_hops(find(p), find(q));
  }

  void print() const;

private:
  vector<node*> nodes;

};

#endif

