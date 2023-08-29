#pragma once
#include <climits>
#include <stack>
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EStatus;

// the type of vertex, the type of edge
template <typename Tv, typename Te> class Graph {
private:
  // Reset the information of all vertices and edges
  void reset() {
    for (int i = 0; i < n; i++) {
      status(i) = UNDISCOVERED;
      dtime(i) = ftime(i) = -1;
      parent(i) = -1;
      priority(i) = INT_MAX;

      for (int j = 0; j < n; j++) {
        if (exists(i, j)) {
          status(i, j) = UNDETERMINED;
        }
      }
    }
  }

  void BFS(int, int &){};
  void DFS(int, int &){};
  void BCC(int, int &, std::stack<int> &){};
  bool TSort(int, int &, std::stack<Tv> *){};
  template <typename PU> void PFS(int, PU){};

public:
  // Vertex:
  // the sum of vertex:
  int n;
  Graph() { n = e = 0; }
  virtual int insert(const Tv &) = 0; // insert the vertex, and return the serial number;
  virtual Tv remove(int) = 0;  // delete the vertex and the edge related to it,
                               // return the details about the edge;
  virtual Tv &vertex(int) = 0; // the data of vertex(the vertex must exist);
  virtual int int_degree(int) = 0; // the indegree of vertex(the vertex must exist);
  virtual int out_degree(int) = 0; // the outdegree of vertex(the vertex must exist);
  virtual int first_neighbor(int) = 0; // node's first neighbor;
  virtual int next_neighbor(int, int) = 0;
  virtual VStatus &status(int) = 0; // node's status;
  virtual int &dtime(int) = 0;
  virtual int &ftime(int) = 0;
  virtual int &parent(int) = 0;   // the parent of the node in tarversal;
  virtual int &priority(int) = 0; // the priority of the node in tarversal;

  // We agree here that all undirected graphs are uniformly converted into a
  // pair of directed edges with opposite directions, so that we can regard
  // undirected graphs as a special case of directed graphs Edge: the sum of
  // edges:
  int e;
  virtual bool exists(int, int) = 0;
  virtual void insert(const Te &, int, int, int) = 0;
  virtual Te remove(int, int) = 0;
  virtual EStatus &status(int, int) = 0;
  // the data of edge(int, int):
  virtual Te &edge(int, int) = 0;
  virtual int &weight(int, int) = 0;

  // Algorithm:
  // Breadth first search algorithm:
  void bfs(int){};
  // Deepth first search algorithm:
  void dfs(int){};
  // Decomposition Algorithm of Biconnected Components Based on DFS:
  // (基于DFS的双连通分量分解算法)
  void bcc(int){};
  // Topological sorting algorithm based on DFS:
  // (基于DFS的拓扑排序算法)
  std::stack<Tv> *tsort(int){};
  // Prim's algorithm for minimum spanning tree:
  // (最小支撑树的Prim算法)
  void prim(int){};
  // Shortest path Dijkstra Algorithm:
  void dijkstra(int){};
  // Priority Search Framework:
  // (优先级搜索框架)
  template <typename PU> void pfs(int, PU){};
};
