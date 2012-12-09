#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class graph {
public:
  struct node {
    node(const string& label) : label(label) {}

    string label;
    vector<int> outgoing;
  };

  int insert(const string& label);

  bool connect(const string& p, const string& q) {
    return connect(find(p), find(q));
  }
  
  // shortest path from p to q, returned in reverse order,
  // including the source and destination nodes, or empty 
  // vector if no path available
  vector<string> shortest_path(const string& p, const string& q) {
    return shortest_path(find(p), find(q));
  }

  // minimum hops between p and q, return -1 if not connected
  // or if either not in graph
  int minimum_hops(const string& p, const string& q) {
    return minimum_hops(find(p), find(q));
  }

  void print() const;

private:
  vector<node*> nodes;
  map<string, int> labels;

  int find(const string& label);
  vector<string> shortest_path(int p, int q);

  bool connect(int p, int q);
  int minimum_hops(int p, int q);

};

#endif

