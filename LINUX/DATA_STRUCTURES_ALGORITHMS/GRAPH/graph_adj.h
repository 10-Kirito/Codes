#pragma once
/**
 * Using adjacency list to implement graph:
 */

// The status of vertex:
#include <vector>
typedef enum { UNVISITED, PROCESSING, VISITED, COMPLETED, PENDING } VStatus;

// the struct of vertex:
struct Vertex {
  int data;
  int indegree, outdegree;
  VStatus status;

  Vertex(const int &d)
      : data(d), indegree(0), outdegree(0), status(UNVISITED) {}
  Vertex(const Vertex &rhs)
      : data(rhs.data), indegree(rhs.indegree), outdegree(rhs.outdegree),
        status(rhs.status) {}

  bool operator==(const Vertex &rhs) { return data == rhs.data; }
};

struct Node {
  Vertex _data;
  Node *_next;

  Node(const int &d, Node *next) : _data(d), _next(nullptr) {}
};

class Graph_Adj {
private:
  int vexnum;
  int edgenum;
  std::vector<Vertex> vertexes;
  std::vector<Node *> edges;

public:
  Graph_Adj() : vexnum(0), edgenum(0) {}

  void insert(const int & data) {
    vertexes.push_back(Vertex(data));
    edges.push_back(new Node(data, nullptr));
    

    
  }
  

};
