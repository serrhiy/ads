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
      auto node{ top };
      while (node != nullptr) {
        auto temp{ node };
        node = node->next;
        free(temp);
      }
    }

    List& push(const T& x) {
      const auto node{ new Node{ top, x } };
      if (node == nullptr) throw std::bad_alloc{  };
      top = node;
      return *this;
    }

    Node* getTop() const { return top; }

  private:
    Node* top;
};
