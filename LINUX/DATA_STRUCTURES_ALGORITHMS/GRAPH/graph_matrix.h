#pragma once
/**
 * Using adjacency lists to implement graphs:
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#define INFINITY INT_MAX

// The type of graph:
// --DG: directed graph,
// --DN: directed network,
// --UDG: undirected graph,
// --UDN: undirected network
typedef enum { DG, DN, UDG, UDN } GraphKind;

// The status of vertex:
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

// the struct of edge:
struct Edge {
  int _weight;
  // judge the edge between _begin and _end:
  bool _exist;

  Edge(const int &weight) : _weight(weight), _exist(false) {}
};

// the graph implemented in matrix:
class Graph_Matrix {
private:
  std::vector<Vertex> vertexes; // the set of vertex
  std::vector<std::vector<Edge>> edges;

  int vexnum, edgenum; // the number of vertex and edge
public:
  Graph_Matrix() : vexnum(0), edgenum(0) {}

  void insert(const int &data) {
    // update the details of edge:
    for (int i = 0; i < vexnum; i++) {
      edges[i].push_back(Edge(INFINITY));
    }
    vexnum++;
    // insert a new vector into edges:
    edges.push_back(std::vector<Edge>(vexnum, Edge(INFINITY)));
    // update the set of vertex:
    vertexes.push_back(Vertex(data));
  }

  template <typename... Args> void insert(const int &data, Args... args) {
    insert(data);
    insert(args...);
  }

  void insert_edge(std::pair<int, int> edge, const int &weight) {
    // find the index of the two nodes:
    std::vector<Vertex>::difference_type index_first =
        std::find_if(
            vertexes.begin(), vertexes.end(),
            [edge](const Vertex &temp) { return temp.data == edge.first; }) -
        vertexes.begin();

    std::vector<Vertex>::difference_type index_second =
        std::find_if(
            vertexes.begin(), vertexes.end(),
            [edge](const Vertex &temp) { return temp.data == edge.first; }) -
        vertexes.begin();

    if (index_first == vexnum || index_second == vexnum) {
      return;
    }

    edges[index_first][index_second]._exist = true;
    edges[index_first][index_second]._weight = weight;
  }

  void show() {
    for (int i = 0; i < vexnum; i++) {
      for (int j = 0; j < vexnum; j++) {
        std::cout << ((edges[i][j]._weight == INFINITY) ? -1
                                                        : edges[i][j]._weight)
                  << " ";
      }
      std::cout << std::endl;
    }
  }
};
