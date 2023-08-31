#include "./include/graph_adj.h"
#include <utility>

int main(int argc, char *argv[]) {
  std::cout << "graph adjacency list test:" << std::endl;
  Graph_Adj graph;
  graph.insert(10, 20, 30, 40, 50, 60);
  graph.insert_edge({{10, 20}, {20, 30}});
  graph.show();

  std::cout << std::endl;
  std::cout << "graph inverse adjacency list test:" << std::endl;
  Graph_Adj graph_inverse;
  graph_inverse.insert(1, 2, 3, 4);
  graph_inverse.insert_edge({{1, 2}, {1, 3}, {4, 1}, {3, 4}}, INVERSE_ADJ());
  graph_inverse.show();

  return 0;
}
