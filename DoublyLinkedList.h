#ifndef LB3_DOUBLYLINKEDLIST_H
#define LB3_DOUBLYLINKEDLIST_H

#include "LinkedList.h"

template<typename T>
class DoublyLinkedList : public LinkedList<T> {

    struct Node {
        Node *pPrev;
        Node *pNext;
        T data;

       explicit Node(const T &, Node * = nullptr, Node * = nullptr);
    };

protected:
    Node *get_node(size_t);

    T delete_node(Node *);

    Node *head;
    Node *tail;

public:
    DoublyLinkedList();

    ~DoublyLinkedList();

    T &at(size_t);

    T &operator[](size_t);

    String toString();

    void push_back(const T &);

    void push_front(const T &);

    void insert(const T &, size_t);

    T pop_back();

    T pop_front();

    T erase(size_t);

    void clear();
};

template<typename T>
DoublyLinkedList<T>::Node::Node(const T &data, DoublyLinkedList::Node *pPrev, DoublyLinkedList::Node *pNext) {
    this->pNext = pNext;
    this->pPrev = pPrev;
    this->data = data;
}//

template<typename T>
typename DoublyLinkedList<T>::Node *DoublyLinkedList<T>::get_node(const size_t position) {
    Node *node;
    if (position < this->_size / 2) {
        node = head;
        for (int counter = 0; counter < position and node->pNext != nullptr; counter++)
            node = node->pNext;
    } else {
        node = tail;
        for (int counter = this->_size - 1; counter > position and node->pPrev != nullptr; counter--)
            node = node->pPrev;
    }
    return node;
}//

template<typename T>
T DoublyLinkedList<T>::delete_node(DoublyLinkedList::Node *node) {
    T data = node->data;
    this->_size--;
    delete (node);
    return data;
}//

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : LinkedList<T>() {
    tail = nullptr;
    head = nullptr;
}//

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}//

template<typename T>
T &DoublyLinkedList<T>::at(const size_t position) {
    if (position >= this->_size)
        throw std::out_of_range(String("{} is more then {}").format(int(position)).format(int(this->_size)));
    return get_node(position)->data;
}//

template<typename T>
T &DoublyLinkedList<T>::operator[](size_t position) {
    return get_node(position)->data;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T &data) {
    if (this->_size == 0) {
        head = new Node(data);
        tail = head;
    } else {
        Node *previousNode = tail;
        Node *newNode = new Node(data, tail);
        previousNode->pNext = newNode;
        tail = newNode;
    }
    this->_size++;
}//

template<typename T>
void DoublyLinkedList<T>::push_front(const T &data) {
    if (this->_size == 0) {
        head = new Node(data);
        tail = head;
    } else {
        Node *nextNode = head;
        Node *newNode = new Node(data, nullptr, head);
        nextNode->pPrev = newNode;
        head = newNode;
    }
    this->_size++;
}//

template<typename T>
void DoublyLinkedList<T>::insert(const T &data, const size_t position) {
    if (position == 0)
        push_front(data);
    else if (position >= this->_size - 1)
        push_back(data);
    else {
        Node *previousNode = get_node(position - 1);
        Node *nextNode = previousNode->pNext;
        Node *newNode = new Node(data, previousNode, nextNode);
        previousNode->pNext = newNode;
        nextNode->pPrev = newNode;
    }
    this->_size++;
}//

template<typename T>
T DoublyLinkedList<T>::pop_back() {
    Node *node = tail;
    if (node->pNext != nullptr) {
        Node *previousNode = tail->pPrev;
        previousNode->pNext = nullptr;
        tail = previousNode;
    } else {
        head = nullptr;
    }
    return delete_node(node);
}//

template<typename T>
T DoublyLinkedList<T>::pop_front() {
    Node *node = head;
    if (node->pNext != nullptr) {
        Node *nextNode = node->pNext;
        nextNode->pPrev = nullptr;
        head = nextNode;
    } else {
        head = nullptr;
    }
    return delete_node(node);
}//

template<typename T>
T DoublyLinkedList<T>::erase(const size_t position) {
    if (position <= 0)
        return pop_front();
    if (position >= this->_size - 1)
        return pop_back();
    Node *node = get_node(position-1);
    Node *previousNode = node->pPrev;
    Node *nextNode = node->pNext;
    previousNode->pNext = nextNode;
    nextNode->pPrev = previousNode;
    return delete_node(node);
}//

template<typename T>
void DoublyLinkedList<T>::clear() {
    if (this->_size != 0) {
        std::function<void(Node *)> clear_all = [&clear_all](Node *node) {
            if (node->pNext != nullptr)
                clear_all(node->pNext);
            delete (node);
        };
        clear_all(head->pNext);
        this->_size = 0;
        head = nullptr;
        tail = nullptr;
    }
}

template<typename T>
String DoublyLinkedList<T>::toString() {
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

#endif //LB3_DOUBLYLINKEDLIST_H
