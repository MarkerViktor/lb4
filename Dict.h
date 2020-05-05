#ifndef LB4_DICT_H
#define LB4_DICT_H

#include <iostream>

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

    Node* root;
    size_t size;
    size_t depth;

    static Node* get_node_by_key(const TKey& key, Node* node) {
        if (key == node->key) {
            return node;
        }
        if (key > node->key) {
            if (node->pRight != nullptr) {
                return get_node_by_key(key, node->pRight);
            }
            node->pRight = new Node(key);
            return node->pRight;
        } else {
            if (node->pLeft != nullptr) {
                return get_node_by_key(key, node->pLeft);
            }
            node->pLeft = new Node(key);
            return node->pLeft;
        }
    }

    static Node* get_node_by_value(const TValue& key, Node* node) {

    }

public:
    TValue& operator[](const TKey& key) {
        if (this->root == nullptr) {
            this->root = new Node(key);
            return this->root->value;
        }
        return get_node_by_key(key, this->root)->value;
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
};

#endif //LB4_DICT_H
