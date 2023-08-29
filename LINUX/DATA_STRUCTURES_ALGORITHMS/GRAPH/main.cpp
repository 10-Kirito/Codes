#include "graph_matrix.h"
#include <utility>

int main(int argc, char *argv[]) {
  Graph_Matrix graph;
  graph.insert(1, 2, 3, 4, 5, 6);
  std::cout << "Graph initializaiton:" << std::endl;
  graph.show();

  graph.insert_edge(std::make_pair(1, 2), 10);
  graph.insert_edge(std::make_pair(4, 5), 20);
  std::cout << "After insert a new edge:" << std::endl;
  graph.show();

}
