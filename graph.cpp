#include "graph.h"
#include <iostream>
#include <queue>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::queue;
using std::map;

int graph::find(const string& label) {
  if(labels.count(label)) {
    return labels[label];
  } else {
    return -1;
  }
}

int graph::insert(const string& label) {
  nodes.push_back(new node(label));

  int id = nodes.size() - 1;
  labels[label] = id;
  return id;
}

bool graph::connect(int p, int q) {
  if(p == -1 || q == -1) {
    return false;
  } else {
    nodes[p]->outgoing.push_back(q);
    return true;
  }
}

int graph::minimum_hops(int source, int destination) {
  if(source == -1 || destination == -1) return -2;

  vector<bool> known(nodes.size());
  vector<int> distance(nodes.size(), -1);
  vector<int> predecessor(nodes.size(), -1);
  queue<int> queue;
  
  queue.push(source);
  distance[source] = 0;

  while(!queue.empty()) {
    int p = queue.front(); queue.pop();
    known[p] = true;

    int new_distance = 1 + distance[p];
    for(int q : nodes[p]->outgoing) {
      if(distance[q] == -1 || new_distance < distance[q]) {
        distance[q] = new_distance;
        predecessor[q] = p;
      }
      if(!known[q]) queue.push(q);
    }
  }

  return distance[destination];
}

void graph::print() const {
  using namespace std;

  for(node* p : nodes) {
    cout << p->label << ':';
    for(int id : p->outgoing) {
      cout << ' ' << nodes[id]->label;
    }
    cout << endl;
  }
}

