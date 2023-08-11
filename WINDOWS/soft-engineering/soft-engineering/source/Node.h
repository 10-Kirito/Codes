/**
 * @copyright 2023 Feb 6 By Yuan Liu
 * @file Node.h
 *
 * This file includes the definition of all the node classes.
 */
#ifndef _SOFTWARE_ENGINEERING__SOURCE__NODE_H_
#define _SOFTWARE_ENGINEERING__SOURCE__NODE_H_

#include <memory>

namespace NODE {

  template<typename T>
  class Node;

#define DELETER_

  template<typename T>
  DELETER_ void delete_node(Node<T> *node) {}

  /**
   * @brief This is s simple example to show how to write a doxygen comment.
   *
   * The following is a small example of a forward-list node. It stores a template
   * data member and a smart pointer which points the next node.
   *
   * @tparam T The type of the data stored in the node.
   */
  template<typename T>
  class Node {
   public:
    /**
     * This function constructs a new `Node` with provided params. If none is provided,
     * all the data members will be constructed by default.
     * @param data The data the user wants the node to store.
     * @param next The next node of current node, default as `nullptr`.
     */
    inline Node(T data = {}, Node<T> *next = nullptr,
                void (*deleter)(Node<T> *) = delete_node) :
            _data(data),
            _next(next, deleter) {}

    Node(const Node &other) = delete;

    Node(Node &&other) = delete;

    ~Node() = default;

    /**
     * Set the data of node.
     * @param data The new data.
     */
    inline void set_data(T data) { this->_data = data; }

    /**
     * Set the next node of current node.
     * @param next The new next node.
     */
    inline void set_next(std::shared_ptr<Node<T>> next) { this->_next = next; }

    /**
     * Get the data of this node.
     * @return The constant data of this node.
     */
    inline const T get_data() const { return _data; }

    /**
     * Get the next node of this node.
     * @return The constant shared ptr of the next node.
     */
    inline const std::shared_ptr<Node<T>> get_next() const { return _next; }

   private:
    /**
     * The data stored in the node.
     */
    T _data;
    /**
     * The next node of current node.
     */
    std::shared_ptr<Node<T>> _next;
  };

}
#endif