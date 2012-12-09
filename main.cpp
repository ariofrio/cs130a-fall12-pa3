#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "graph.h"

using std::vector;
using std::string; using std::stringstream;
using std::cin; using std::cout; using std::cerr;
using std::endl;

int main(int argc, char** argv) {
  graph graph;

  while(!cin.eof()) {
    string line; getline(cin, line);

    // split into tokens
    vector<string> tokens;
    {
      stringstream ss(line);
      string buf;
      while(ss >> buf) {
        tokens.push_back(buf);
      }
    }

    if(tokens.size() == 1 &&
       strtol(line.c_str(), NULL, 10) != 0) {
      // ignore, we are smart: we don't need no numbers!
      // (we are smart, we are kind, we are important)
      ;
    } else if(line.compare("_ print") == 0) {
      graph.print();
    } else if(tokens.size() == 1) { // add new node
      // add new node
      graph.insert(tokens[0]);
    } else if(tokens.size() == 3 && 
              tokens[1].compare("follows") == 0) {
      // add new connection
      graph.connect(tokens[0], tokens[2]);
    } else if(tokens.size() == 2) {
      // find minimum hops
      cout << graph.minimum_hops(tokens[0], tokens[1])
           << endl;
    }
  }
}

