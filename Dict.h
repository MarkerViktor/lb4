#ifndef LB4_DICT_H
#define LB4_DICT_H

#include <functional>
#include "LinkedList.h"
#include "String.h"

class NotExist : public std::runtime_error {
public:
    NotExist(const char* string) : std::runtime_error(string) {};
};

template<typename TKey, typename TValue>
class Dict {

    struct Node {
        TKey key;
        TValue value;
        Node *pRight;
        Node *pLeft;

        Node(const TKey &key, Node *pRight = nullptr, Node *pLeft = nullptr) {
            this->key = key;
            this->pRight = pRight;
            this->pLeft = pLeft;
        }
    };

    Node *root;
    size_t size;
    size_t depth;

    Node *create_node(const TKey &key, Node *pRight = nullptr, Node *pLeft = nullptr) {
        this->size++;
        return new Node(key, pRight, pLeft);
    }

    TValue delete_node(Node *node) {
        TValue value = node->value;
        delete node;
        return value;
    }

    Node *find_node_by_value(const TValue &value) {
        Node *node = nullptr;
        auto value_checker = [&node, &value](Node *node_) {
            if (node_->value == value) {
                node = node_;
                throw StopTraversal();
            }
        };
        try {
            traversal_in_order(this->root, value_checker);
        } catch (StopTraversal exception) {}
        return node;
    }

    Node *find_node_by_key(const TKey &key, Node *node) {
        if (key == node->key) {
            return node;
        }
        if (key > node->key) {
            if (node->pRight != nullptr) {
                return find_node_by_key(key, node->pRight);
            }
            return nullptr;
        } else {
            if (node->pLeft != nullptr) {
                return find_node_by_key(key, node->pLeft);
            }
            return nullptr;
        }
    }

    Node *get_node_with_key(const TKey &key, Node *node) {
        if (key == node->key) {
            return node;
        }
        if (key > node->key) {
            if (node->pRight != nullptr) {
                return get_node_with_key(key, node->pRight);
            }
            node->pRight = create_node(key);
            return node->pRight;
        } else {
            if (node->pLeft != nullptr) {
                return get_node_with_key(key, node->pLeft);
            }
            node->pLeft = create_node(key);
            return node->pLeft;
        }
        /*while (true) {
            if (key == node->key) {
                return node;
            }
            if (key > node->key) {
                if (node->pRight != nullptr) {
                    node = node->pRight;
                    continue;
                }
                node->pRight = create_node(key);
                return node->pRight;
            } else {
                if (node->pLeft != nullptr) {
                    node = node->pLeft;
                    continue;
                }
                node->pLeft = create_node(key);
                return node->pLeft;
            }
        }*/

    }

    void traversal(Node *node, std::function<void(Node *)> func) {
        if (node->pLeft != nullptr)
            traversal(node->pLeft, func);
        if (node->pRight != nullptr)
            traversal(node->pRight, func);
        func(node);
    }

    void traversal_in_order(Node *node, std::function<void(Node *)> func) {
        if (node->pLeft != nullptr)
            traversal_in_order(node->pLeft, func);
        func(node);
        if (node->pRight != nullptr)
            traversal_in_order(node->pRight, func);
    }

public:
    TValue &operator[](const TKey &key) {
        if (this->root == nullptr) {
            this->root = new Node(key);
            return this->root->value;
        }
        return get_node_with_key(key, this->root)->value;
    }

    TKey getKey(const TValue &value) {
        Node* node = find_node_by_value(value);
        if (node == nullptr)
            throw NotExist("A pair with the value does not exist");
        return node->key;
    }

    LinkedList<TKey> getKeysList() {
        auto list = new LinkedList<TKey>();
        traversal_in_order(root, [list](Node *node) { list->push_back(node->key); });
        return *list;
    }

    LinkedList<TKey> getValuesList() {
        auto list = new LinkedList<TKey>();
        traversal(root, [list](Node *node) { list->push_back(node->value); });
        return *list;
    }

    TValue pop(const TKey &key) {
        Node *node = find_node_by_key(key, this->root);
        if (node == nullptr) {
            throw NotExist("A pair with the key does not exist");
        }
        TValue value = node->value;
        //if

    }

    void clear() {
        traversal(this->root, [](Node *node) { delete (node); });
        this->size = 0;
        this->depth = 0;
        this->root = nullptr;
    }

    size_t getSize() const {
        return size;
    }

    size_t getDepth() const {
        return depth;
    }

    Dict<TKey, TValue>() {
        this->root = nullptr;
        this->size = 0;
        this->depth = 0;
    }

    ~Dict() {
        if (this->size != 0)
            this->clear();
    }

    class StopTraversal : public std::exception {
    };
};

#endif //LB4_DICT_H
