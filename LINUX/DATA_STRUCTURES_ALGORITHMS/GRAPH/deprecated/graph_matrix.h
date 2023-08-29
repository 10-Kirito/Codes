#pragma once
#include "graph.h"
#include <vector>

template <typename Tv> struct Vertex {
  Tv data;
  int inDegree, outDegree;
  VStatus status;
  // discovery time and finish time:
  // These two time tags are mainly used in algorithms such as depth-first
  // search (DFS) and topological sorting in graph algorithms. By recording the
  // access times of vertices, information about the order and dependencies of
  // vertex visits can be obtained during the execution of the algorithm
  int dTime, fTime;
  int parent;
  int priority;
  explicit Vertex(const Tv &d = 0)
      : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1),
        fTime(-1), parent(-1), priority(INT_MAX) {}
};

template <typename Te> struct Edge {
  Te data;
  int weight;
  // These states are related to the traversal algorithm of the graph,
  // especially the DFS algorithm
  EStatus status;
  Edge(const Te &d, int w) : data(d), weight(w), status(UNDETERMINED) {}

  // typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EStatus;
};

// Graph based on vector and adjacency matrix implementation
template <typename Tv, typename Te> class GraghMatrix : public Graph<Tv, Te> {
private:
  std::vector<Vertex<Tv>> V;              // the set of Vertexes
  std::vector<std::vector<Edge<Te> *>> E; // the set of Edges

public:
  GraghMatrix() { this->n = this->e = 0; }
  ~GraghMatrix() {
    for (int j = 0; j < this->n; j++) {
      for (int k = 0; k < this->n; k++) {
        delete E[j][k];
      }
    }
  }

  // basic operations in graph: query the i-th vertex
  Tv &vertex(int i) override { return V[i].data; }
  int int_degree(int i) override { return V[i].inDegree; }
  int out_degree(int i) override { return V[i].outDegree; }
  int first_neighbor(int i) override { return next_neighbor(i, this->n); }
  int next_neighbor(int i, int j) override {}
  VStatus &status(int i) override { return V[i].states; }
  int &dtime(int i) override { return V[i].dTime; }
  int &ftime(int i) override { return V[i].fTime; }
  int &parent(int i) override { return V[i].parent; }
  int &priority(int i) override { return V[i].priority; }

  // vertex's dynamic operations
  int insert(const Tv &vertex) override {
    for (int j = 0; j < this->n; j++) {
      E[j].insert(nullptr);
    }
    this->n++;

  }

  bool exists(int, int) override{};
  void insert(const Te &, int, int, int) override{};
  Te remove(int, int) override{};
  EStatus &status(int, int) override{};
  // the data of edge(int, int):
  Te &edge(int, int) override{};
  int &weight(int, int) override{};
};
