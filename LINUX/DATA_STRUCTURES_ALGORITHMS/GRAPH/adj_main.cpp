#include "./include/graph_adj.h"
#include <iostream>
#include <utility>

void visit(const int &data) { std::cout << data << " "; }

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

  std::cout << std::endl;
  std::cout << "graph dfs traversal test:" << std::endl;
  graph.dfs_traversal(visit);
  std::cout << std::endl;
  std::cout << std::endl;

  Graph_Adj graph_1;
  graph_1.insert(1, 2, 3, 4, 5, 6, 7, 8);

  graph_1.insert_edge(
      {{1, 2}, {2, 4}, {2, 5}, {4, 8}, {5, 8}, {1, 3}, {3, 6}, {3, 7}, {6, 7}});
  graph_1.show();
  std::cout << std::endl;


  graph_1.dfs_traversal(visit);
  std::cout << std::endl;
  graph_1.bfs_traversal(visit);
  std::cout << std::endl;

  return 0;
}
