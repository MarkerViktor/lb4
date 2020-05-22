#ifndef LB3_LINCKEDLIST_H
#define LB3_LINCKEDLIST_H

#include <functional>
#include "String.h"
#include <stdexcept>

template<typename T>
class LinkedList {

protected:
    struct Node {
        Node *pNext;
        T data;

        explicit Node(const T &data, Node *pNext = nullptr);
    };

    size_t _size;

    Node *head;

    Node *get_node(size_t);

    T delete_node(Node *);

public:
    LinkedList();

    ~LinkedList();

    size_t size();

    virtual T &at(size_t);

    virtual T &operator[](size_t);

    virtual String toString();

    virtual void push_back(const T &);

    virtual void push_front(const T &);

    virtual void insert(const T &, size_t);

    virtual T pop_back();

    virtual T pop_front();

    virtual T erase(size_t);

    void clear_all(Node *);

    virtual void clear();
};


template<typename T>
LinkedList<T>::Node::Node(const T &data, LinkedList::Node *pNext) {
    this->data = data;
    this->pNext = pNext;
}//

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::get_node(const size_t position) {
    Node *node = head;
    for (int counter = 0; counter < position and node->pNext != nullptr; counter++)
        node = node->pNext;
    return node;
}//

template<typename T>
T LinkedList<T>::delete_node(LinkedList::Node *node) {
    T data = node->data;
    delete (node);
    _size--;
    return data;
}//

template<typename T>
LinkedList<T>::LinkedList() {
    _size = 0;
    head = nullptr;
}//

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}//

template<typename T>
size_t LinkedList<T>::size() {
    return _size;
}//

template<typename T>
T &LinkedList<T>::at(const size_t position) {
    if (position >= _size)
        throw std::out_of_range(String("{} is more then {}").format(int(position)).format(int(_size)));
    return get_node(position)->data;
}//

template<typename T>
T &LinkedList<T>::operator[](size_t position) {
    return get_node(position)->data;
}//

template<typename T>
void LinkedList<T>::push_back(const T &data) {
    if (_size == 0)
        head = new Node(data);
    else
        get_node(_size - 1)->pNext = new Node(data);
    _size++;
}//

template<typename T>
void LinkedList<T>::push_front(const T &data) {
    head = new Node(data, head);
    _size++;
}//

template<typename T>
void LinkedList<T>::insert(const T &data, const size_t position) {
    if (position == 0)
        push_front(data);
    else if (position >= _size - 1)
        push_back(data);
    else {
        Node *previousNode = get_node(position - 1);
        Node *newNode = new Node(data, previousNode->pNext);
        previousNode->pNext = newNode;
    }
    _size++;
}//

template<typename T>
T LinkedList<T>::pop_back() {
    Node *previousNode = get_node(_size - 2);
    Node *node = previousNode->pNext;
    previousNode->pNext = nullptr;
    return delete_node(node);
}//

template<typename T>
T LinkedList<T>::pop_front() {
    Node *node = head;
    Node *nextNode = node->pNext;
    head = nextNode;
    return delete_node(node);
}//

template<typename T>
T LinkedList<T>::erase(const size_t position) {
    if (position <= 0)
        return pop_front();
    if (position >= _size - 1)
        return pop_back();
    Node *previousNode = get_node(position - 1);
    Node *node = previousNode->pNext;
    Node *nextNode = node->pNext;
    previousNode->pNext = nextNode;
    return delete_node(node);
}//

template<typename T>
void LinkedList<T>::clear_all(Node *node) {
    if (node->pNext != nullptr)
        clear_all(node->pNext);
    delete (node);
}//

template<typename T>
void LinkedList<T>::clear() {
    if (_size != 0) {
        clear_all(this->head->pNext);
        this->_size = 0;
        this->head = nullptr;
    }
}//

template<typename T>
String LinkedList<T>::toString() {
    Node *node = head;
    String string = "[";
    if (node != nullptr) {
        while (node->pNext != nullptr) {
            string += std::to_string(node->data) + ",\t";
            node = node->pNext;
        }
        string += std::to_string(node->data);
    }
    string += "]";
    return string;
}


#endif //LB3_LINCKEDLIST_H