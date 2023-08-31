#pragma once

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
struct ArcNode;

// the vertex nodes:
struct Vertex {
  int _data;
  ArcNode *_firstin;
  ArcNode *_firstout;

  Vertex(const int &data, ArcNode *firstin = nullptr,
         ArcNode *firstout = nullptr)
      : _data(data), _firstin(firstin), _firstout(firstout) {}

  Vertex(const Vertex &rhs) {
    _data = rhs._data;
    _firstin = rhs._firstin;
    _firstout = rhs._firstout;
  }

  friend std::ostream &operator<<(std::ostream &out, const Vertex &vertex) {
    out << vertex._data;
    return out;
  }
};

// the arc nodes:
struct ArcNode {
  Vertex _headvex, _tailvex;

  ArcNode *hlink;
  ArcNode *tlink;

  ArcNode(Vertex headvex, Vertex tailvex, ArcNode *headlink = nullptr,
          ArcNode *taillink = nullptr)
      : _headvex(headvex), _tailvex(tailvex), hlink(headlink), tlink(taillink) {
  }

  ArcNode(int headvex, int tailvex, ArcNode *headlink = nullptr,
          ArcNode *taillink = nullptr)
      : _headvex(headvex), _tailvex(tailvex), hlink(headlink), tlink(taillink) {
  }

  friend std::ostream &operator<<(std::ostream &out, ArcNode &node) {
    out << "[" << node._headvex << "," << node._tailvex << "]";
    return out;
  }
};

// implement graph using orth-list:
class GraphOrthList {
private:
  int vexnum;
  int arcnum;

  std::vector<Vertex> vertexes;

public:
  GraphOrthList() : vexnum(0), arcnum(0) {}

  // insert new vertexes:
  void insert(const int &);
  template <typename... Args> void insert(const int &, Args...);
  // insert new arc nodes:
  void insert_edge(const std::pair<int, int> &);
  void insert_edge(const std::initializer_list<std::pair<int, int>> &);

  // return the indegree and outdegree of vertex in graph:
  int indegree(const int &);
  int outdegree(const int &);

  // show the graph:
  void show() const;
};

inline void GraphOrthList::insert(const int &data) {
  vertexes.push_back(Vertex(data));
  vexnum++;
}

template <typename... Args>
inline void GraphOrthList::insert(const int &data, Args... args) {
  insert(data);
  insert(args...);
}

// insert arc nodes:
inline void GraphOrthList::insert_edge(const std::pair<int, int> &edge) {
  int first_num = edge.first;
  int second_num = edge.second;

  auto iter_1 = std::find_if(
      vertexes.begin(), vertexes.end(),
      [first_num](const Vertex &vertex) { return vertex._data == first_num; });

  auto iter_2 = std::find_if(vertexes.begin(), vertexes.end(),
                             [second_num](const Vertex &vertex) {
                               return vertex._data == second_num;
                             });

  // check the value if exist:
  if (iter_1 == vertexes.end() || iter_2 == vertexes.end()) {
    throw std::invalid_argument("received value isn't exist.");
  }

  // update the related in_list and out_list;
  // first_num ----->  second_num

  ArcNode *outhead = vertexes[iter_1 - vertexes.begin()]._firstout;
  ArcNode *inhead = vertexes[iter_2 - vertexes.begin()]._firstin;

  ArcNode *newNode = new ArcNode(first_num, second_num);

  if (outhead == nullptr) {
    vertexes[iter_1 - vertexes.begin()]._firstout = newNode;
  } else {
    while (outhead->tlink) {
      outhead = outhead->tlink;
    }
    outhead->tlink = newNode;
  }

  if (inhead == nullptr) {
    vertexes[iter_2 - vertexes.begin()]._firstin = newNode;
  } else {
    while (inhead->hlink) {
      inhead = inhead->hlink;
    }
    inhead->hlink = newNode;
  }
  arcnum++;
}

inline void GraphOrthList::insert_edge(
    const std::initializer_list<std::pair<int, int>> &data) {
  for (const auto &elem : data) {
    insert_edge(elem);
  }
}

// return the indegree and outdegree in graph:
inline int GraphOrthList::indegree(const int &data) {

  auto iter = std::find_if(
      vertexes.begin(), vertexes.end(),
      [data](const Vertex &vertex) { return vertex._data == data; });

  if (iter == vertexes.end()) {
    throw std::invalid_argument("the vertex isn't exist.");
  }

  ArcNode *head = vertexes[iter - vertexes.begin()]._firstin;

  int count = 0;

  while (head) {
    count++;
    head = head->hlink;
  }

  return count;
}

inline int GraphOrthList::outdegree(const int &data) {
  auto iter = std::find_if(
      vertexes.begin(), vertexes.end(),
      [data](const Vertex &vertex) { return vertex._data == data; });

  if (iter == vertexes.end()) {
    throw std::invalid_argument("the vertex isn't exist.");
  }

  ArcNode *head = vertexes[iter - vertexes.begin()]._firstout;

  int count = 0;

  while (head) {
    count++;
    head = head->tlink;
  }

  return count;

}

// show the details of graph:
inline void GraphOrthList::show() const {

  for (const auto &vertex : vertexes) {
    // outlist:
    std::cout << vertex;
    std::cout << "====>";
    ArcNode *head = vertex._firstout;
    while (head) {
      std::cout << *head;
      if (head->tlink) {
        std::cout << "====>";
      }
      head = head->tlink;
    }
    std::cout << std::endl;

    // inlist:
    std::cout << vertex;
    std::cout << "====>";
    ArcNode *tail = vertex._firstin;
    while (tail) {
      std::cout << *tail;
      if (tail->hlink) {
        std::cout << "====>";
      }
      tail = tail->hlink;
    }
    std::cout << std::endl;
  }
}
