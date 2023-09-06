#pragma once
/**
 * Using adjacency list to implement graph:
 */

// The status of vertex:
#include <algorithm>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

// distinguish whether the adjacency list is an inverse adjacency list:
struct INVERSE_ADJ {};
struct ADJ {};

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
  Vertex _vertex;
  Node *_next;
  VStatus status;

  Node(const int &d, Node *next)
      : _vertex(d), _next(nullptr), status(UNVISITED) {}
};

class Graph_Adj {
private:
  int vexnum;
  int edgenum;
  std::vector<Vertex> vertexes;
  std::vector<Node *> edges;

  // traversal algorithm:
  void dfs(Node *node, void (*visit)(const int &)) {
    // find the node's location in edges:
    auto ptr = std::find_if(edges.begin(), edges.end(),
                            [node](const std::vector<Node *>::value_type &val) {
                              return val->_vertex == node->_vertex;
                            });
    // if don't find the node, return
    if (ptr == edges.end()) {
      return;
    }
    node = edges[ptr - edges.begin()];

    // if the node has been visited, return
    if (node->status == VISITED) {
      return;
    }

    // visit the node:
    node->status = VISITED;
    visit(node->_vertex.data);

    for (; node != nullptr; node = node->_next) {
      if (node->status == UNVISITED) {
        dfs(node, visit);
      }
    }
  }

public:
  Graph_Adj() : vexnum(0), edgenum(0) {}

  // insert the new vertex:
  void insert(const int &);
  template <typename... Args> void insert(const int &, Args...);

  // insert the new edges:
  void insert_edge(const std::pair<int, int> &);
  template <typename... Args>
  void insert_edge(const std::pair<int, int> &, Args...);
  void insert_edge(const std::initializer_list<std::pair<int, int>> &);

  // inverse adjacency list operation:
  void insert_edge(const std::pair<int, int> &, INVERSE_ADJ);
  void insert_edge(const std::initializer_list<std::pair<int, int>> &,
                   INVERSE_ADJ);

  // return true if the number of edges is zero
  bool empty() const { return edgenum == 0; }

  // tarversal algorithm:
  // 1.BFS, Breadth_First Search:
  void bfs_traversal(void (*visit)(const int &)) {
    // reset all nodes of graph:
    for (int i = 0; i < edges.size(); i++) {
      edges[i]->status = UNVISITED;
    }

    std::queue<Node *> queue;

    if (empty()) {
      return;
    }
    queue.push(edges[0]);

    while (!queue.empty()) {
      Node *node = queue.front();
      if (node->status == UNVISITED) {
        visit(node->_vertex.data);
        node->status = VISITED;
      }
      queue.pop();

      for (node = node->_next; node != nullptr; node = node->_next) {
        auto ptr =
            std::find_if(edges.begin(), edges.end(),
                         [node](const std::vector<Node *>::value_type &val) {
                           return val->_vertex == node->_vertex;
                         });

        queue.push(edges[ptr - edges.begin()]);
      }
    }
  }
  //
  // 2.DFS, Depth_First Search:
  void dfs_traversal(void (*visit)(const int &)) {
    for (int i = 0; i < edges.size(); i++) {
      edges[i]->status = UNVISITED;
    }

    for (int i = 0; i < edges.size(); i++) {
      if (edges[i]->status == UNVISITED) {
        dfs(edges[i], visit);
      }
    }
  }

  // show the details of the graph_adj:
  void show() const;
};

// insert the new vertex:
inline void Graph_Adj::insert(const int &data) {
  vexnum++;
  vertexes.push_back(Vertex(data));
  edges.push_back(new Node(data, nullptr));
}

template <typename... Args>
inline void Graph_Adj::insert(const int &data, Args... args) {
  insert(data);
  insert(args...);
}
// insert the new vertex ends
//
// insert the new edges:
inline void Graph_Adj::insert_edge(const std::pair<int, int> &edge) {
  int first_num = edge.first;
  int second_num = edge.second;

  auto iter_1 = std::find_if(
      vertexes.begin(), vertexes.end(),
      [first_num](const Vertex &vertex) { return vertex.data == first_num; });

  auto iter_2 = std::find_if(
      vertexes.begin(), vertexes.end(),
      [second_num](const Vertex &vertex) { return vertex.data == second_num; });

  // check the vertex if exist:
  if (iter_1 == vertexes.end() || iter_2 == vertexes.end()) {
    throw std::invalid_argument("received value isn't exist.");
  }

  // the two vertexes all exist:
  Node *head = edges[iter_1 - vertexes.begin()];

  while (head->_next) {
    head = head->_next;
  }

  head->_next = new Node(second_num, nullptr);
  edgenum++;
}

template <typename... Args>
inline void Graph_Adj::insert_edge(const std::pair<int, int> &edge,
                                   Args... args) {
  insert_edge(edge);
  insert_edge(args...);
}

inline void
Graph_Adj::insert_edge(const std::initializer_list<std::pair<int, int>> &data) {
  for (const auto &edge : data)
    insert_edge(edge);
}

// insert edges ends
//
// insert inverse adjacency edges:
inline void Graph_Adj::insert_edge(const std::pair<int, int> &edge,
                                   INVERSE_ADJ) {
  int first_num = edge.first;
  int second_num = edge.second;

  auto iter_1 = std::find_if(
      vertexes.begin(), vertexes.end(),
      [first_num](const Vertex &vertex) { return vertex.data == first_num; });

  auto iter_2 = std::find_if(
      vertexes.begin(), vertexes.end(),
      [second_num](const Vertex &vertex) { return vertex.data == second_num; });

  // check the vertex if exist:
  if (iter_1 == vertexes.end() || iter_2 == vertexes.end()) {
    throw std::invalid_argument("received value isn't exist.");
  }

  Node *head = edges[iter_2 - vertexes.begin()];

  while (head->_next) {
    head = head->_next;
  }

  // head->_next = new Node(first_num, nullptr);
  head->_next = new Node(first_num, nullptr);
}

inline void
Graph_Adj::insert_edge(const std::initializer_list<std::pair<int, int>> &data,
                       INVERSE_ADJ) {
  for (const auto &edge : data)
    insert_edge(edge, INVERSE_ADJ());
}

inline void Graph_Adj::show() const {
  Node *next = nullptr;
  for (const auto &elem : edges) {
    next = elem;
    while (next) {
      std::cout << next->_vertex.data;
      if (next->_next) {
        std::cout << " --> ";
      } else {
        std::cout << " --> NULL";
      }
      next = next->_next;
    }
    std::cout << std::endl;
  }
}
