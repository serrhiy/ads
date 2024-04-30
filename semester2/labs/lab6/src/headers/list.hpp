#pragma once
#include <stdexcept>

template<typename T>
class List {
  public:
    struct Node {
      Node* next;
      T value;
    };

    List(): top{ nullptr }
    {

    }

    ~List() {
      Node* node{ top };
      while (node != nullptr) {
        Node* temp{ node };
        node = node->next;
        delete temp;
      }
    }

    List& push(const T& x) {
      const Node* node{ new Node{ top, x } };
      if (node == nullptr) throw std::bad_alloc{  };
      top = node;
      return *this;
    }

    Node* getTop() const { return top; }

  private:
    Node* top;
};
