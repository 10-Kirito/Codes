#include "./include/graph_orth_list.h"
#include <iostream>

int main(int argc, char *argv[]) {
  GraphOrthList graph;

  graph.insert(1, 2, 3, 4);

  std::cout << "------------------The details of graph:-----------------"
            << std::endl;
  graph.insert_edge({{1, 2}, {1, 3}, {3, 1}, {3, 4}, {4, 3}, {4, 2}, {4, 1}});
  graph.show();

  std::cout << "---------Get the indegree and outdegree of vertex:------"
            << std::endl;
  std::cout << "The indegree of 1 is " << graph.indegree(1);
  std::cout << std::endl;
  std::cout << "The outdegree of 1 is " << graph.outdegree(1);
  std::cout << std::endl;
  std::cout << "The indegree of 2 is " << graph.indegree(2);
  std::cout << std::endl;
  std::cout << "The outdegree of 2 is " << graph.outdegree(2);

  return 0;
}
