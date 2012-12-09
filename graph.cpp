#include "graph.h"
#include <iostream>

using std::string;

graph::node* graph::find(const string& label) {
  // TODO use a std::map to search for this?
  for(node* node : nodes) {
    if(label.compare(node->label) == 0) return node;
  }
  return nullptr;
}

graph::node* graph::insert(const string& label) {
  node* p = new node(label);
  nodes.push_back(p);
  return p;
}

bool graph::connect(node* p, node* q) {
  if(p == nullptr || q == nullptr) {
    return false;
  } else {
    p->outgoing.push_back(q);
    return true;
  }
}

int graph::minimum_hops(node* p, node* q) {
  vector<bool> known(nodes.size());
  vector<int> distance(nodes.size());
  vector<node*> predecessor(nodes.size());

}

void graph::print() const {
  using namespace std;

  for(node* p : nodes) {
    cout << p->label << ':';
    for(node* q : p->outgoing) {
      cout << ' ' << q->label;
    }
    cout << endl;
  }
}

