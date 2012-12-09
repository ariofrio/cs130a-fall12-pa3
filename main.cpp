#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "graph.h"

using std::vector;
using std::string;
using std::cin; using std::cout; using std::cerr;
using std::endl;

// (we are smart, we are kind, we are important)
int main(int argc, char** argv) {
  graph graph;

  int count;
  bool verbose = false, print = false;
  {
    string word;
    cin >> word;
    if(word.compare("verbose+print") == 0) {
      verbose = true;
      print = true;
      cin >> count;
    } else if(word.compare("verbose") == 0) {
      verbose = true;
      cin >> count;
    } else {
      count = strtol(word.c_str(), NULL, 10);
    }
  }

  while(count-- > 0) {
    string label;
    cin >> label;
    graph.insert(label);
  }

  cin >> count;
  while(count-- > 0) {
    string follower, verb, followed;
    cin >> follower >> verb >> followed;
    if(!graph.connect(followed, follower)) {
      cerr << "either " << followed << " or " << follower <<
        " not found in graph" << endl;
    }
  }

  if(print) graph.print();

  cin >> count; // ignored
  while(!cin.eof()) {
    string source, destination;
    cin >> source >> destination;
    if(source.length() == 0 || destination.length() == 0)
      continue;

    cout << graph.minimum_hops(source, destination) << endl;
    if(verbose) {
      vector<string> path =
        graph.shortest_path(source, destination);
      for(const string& label : path) {
        cout << label << ' ';
      }
      cout << endl;
    }
  }
}

