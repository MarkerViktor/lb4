#ifndef LB4_DICT_H
#define LB4_DICT_H

#include <functional>
#include <sstream>
#include <cmath>
#include "LinkedList.h"
#include "String.h"

class NotExist : public std::runtime_error {
public:
    NotExist(const char *string) : std::runtime_error(string) {};
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

    Node *create_node(const TKey &key, Node *pRight = nullptr, Node *pLeft = nullptr) {
        this->size++;
        return new Node(key, pRight, pLeft);
    }

    TValue remove_node(Node *node) {
        this->size--;
        TValue value = node->value;
        delete node;
        return value;
    }

    static Node *find_node_by_value(const TValue &value, Node *first_node) {
        Node *node = nullptr;
        auto value_checker = [&node, &value](Node *node_) {
            if (node_->value == value) {
                node = node_;
                throw StopTraversal();
            }
        };
        traversal_in_order(first_node, value_checker);
        return node;
    }

    static Node *find_node_by_key(const TKey &key, Node *node) {
        /*
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
        */
        while (true) {
            if (key == node->key) {
                return node;
            }
            if (key > node->key) {
                if (node->pRight != nullptr) {
                    node = node->pRight;
                    continue;
                }
                return nullptr;
            } else {
                if (node->pLeft != nullptr) {
                    node = node->pLeft;
                    continue;
                }
                return nullptr;
            }
        }
    }

    Node *get_node_with_key(const TKey &key, Node *first_node) {
        /*if (key == first_node->key) {
            return first_node;
        }
        if (key > first_node->key) {
            if (first_node->pRight != nullptr) {
                return get_node_with_key(key, first_node->pRight);
            }
            first_node->pRight = create_node(key);
            return first_node->pRight;
        } else {
            if (first_node->pLeft != nullptr) {
                return get_node_with_key(key, first_node->pLeft);
            }
            first_node->pLeft = create_node(key);
            return first_node->pLeft;
        }*/
        while (true) {
            if (key == first_node->key) {
                return first_node;
            }
            if (key > first_node->key) {
                if (first_node->pRight != nullptr) {
                    first_node = first_node->pRight;
                    continue;
                }
                first_node->pRight = create_node(key);
                return first_node->pRight;
            } else {
                if (first_node->pLeft != nullptr) {
                    first_node = first_node->pLeft;
                    continue;
                }
                first_node->pLeft = create_node(key);
                return first_node->pLeft;
            }
        }

    }

    static Node *get_prev_node(Node *node, Node *first_node) {
        Node *prevNode;
        traversal(first_node, [node, &prevNode](Node *current_node) {
            if (current_node->pLeft == node || current_node->pRight == node)
                prevNode = current_node;
        });
        return prevNode;
    }

    static void traversal(Node *node, std::function<void(Node *)> func) {
        if (node->pLeft != nullptr)
            traversal(node->pLeft, func);
        if (node->pRight != nullptr)
            traversal(node->pRight, func);
        try { func(node); } catch (StopTraversal &) { return; }
    }

    static void traversal_in_order(Node *node, std::function<void(Node *)> func) {
        if (node->pLeft != nullptr)
            traversal_in_order(node->pLeft, func);
        try { func(node); } catch (StopTraversal &) { return; }
        if (node->pRight != nullptr)
            traversal_in_order(node->pRight, func);
    }
/*
    static void traversal_widely(Node *node, std::function<void(Node *)> func) {
        LinkedList<Node*> queue;
        queue.push_back(node);
        while (queue.size() != 0) {
            try { func(queue.pop_front()); } catch (StopTraversal &) { return; }
            if (node->pLeft != nullptr)
                queue.push_back(node->pLeft);
            if (node->pRight != nullptr)
                queue.push_back(node->pRight);
        }
    }
*/
public:
    TValue &operator[](const TKey &key) {
        if (this->root == nullptr) {
            this->root = create_node(key);
            return this->root->value;
        }
        return get_node_with_key(key, this->root)->value;
    }

    void printKeysTree() {
        auto depth = this->getDepth();
        size_t horizontal_size = pow(2, depth);
        auto levels = std::vector<std::vector<std::string>>(depth, std::vector<std::string>(horizontal_size, "  "));

        std::function<void(Node *, size_t, size_t)> print_traversal =
                [&print_traversal, &levels, &horizontal_size](Node *node, size_t position, size_t current_depth) {
                    levels[current_depth - 1][position - 1] = std::to_string(node->key);
                    if (node->pLeft != nullptr)
                        print_traversal(node->pLeft, position - horizontal_size / pow(2, current_depth + 1),
                                        current_depth + 1);
                    if (node->pRight != nullptr)
                        print_traversal(node->pRight, position + horizontal_size / pow(2, current_depth + 1),
                                        current_depth + 1);
                };
        print_traversal(this->root, horizontal_size / 2, 1);
        for (const auto &level: levels) {
            for (const auto &element: level)
                std::cout << element;
            std::cout << std::endl << std::endl;
        }
    }

    TKey getKey(const TValue &value) {
        Node *node = find_node_by_value(value, this->root);
        if (node == nullptr)
            throw NotExist("A pair with the value does not exist");
        return node->key;
    }

    TValue getValue(const TKey &key) {
        Node *node = find_node_by_key(key, this->root);
        if (node == nullptr)
            throw NotExist("A pair with the key does not exist");
        return node->value;
    }

    LinkedList<TKey> getKeysList() {
        auto list = new LinkedList<TKey>();
        traversal_in_order(root, [list](Node *node) { list->push_back(node->key); });
        return *list;
    }

    LinkedList<TValue> getValuesList() {
        auto list = new LinkedList<TValue>();
        traversal(root, [list](Node *node) { list->push_back(node->value); });
        return *list;
    }

    TValue pop(const TKey &key) {
        Node *node = find_node_by_key(key, this->root);
        if (node == nullptr)
            throw NotExist("A pair with the key does not exist");

        Node *substitute; // замена

        if (node->pLeft == nullptr && node->pRight == nullptr)
            substitute = nullptr;
        else if (node->pLeft != nullptr && node->pRight != nullptr) {
            Node *near_bigger = node->pRight;
            while (near_bigger->pLeft != nullptr)
                near_bigger = near_bigger->pLeft;
            near_bigger->pLeft = node->pLeft;
            substitute = node->pRight;
        } else {
            if (node->pRight == nullptr)
                substitute = node->pLeft;
            else
                substitute = node->pRight;
        }

        if (root->key != key) {
            Node *prevNode = get_prev_node(node, this->root);
            if (prevNode->pRight == node)
                prevNode->pRight = substitute;
            else
                prevNode->pLeft = substitute;
        } else {
            if (node->pRight == nullptr)
                root = node->pLeft;
            else
                root = node->pRight;
        }
        return remove_node(node);
    }

    void clear() {
        if (this->size != 0) {
            traversal(this->root, [](Node *node) { delete (node); });
            this->size = 0;
            this->root = nullptr;
        }
    }

    size_t getSize() const {
        return size;
    }

    size_t getDepth() const {
        size_t depth = 1;
        std::function<void(Node *, size_t)> depth_traversal = [&depth_traversal, &depth](Node *node,
                                                                                         size_t current_depth) {
            if (depth < current_depth)
                depth = current_depth;
            if (node->pLeft != nullptr)
                depth_traversal(node->pLeft, current_depth + 1);
            if (node->pRight != nullptr)
                depth_traversal(node->pRight, current_depth + 1);
        };
        depth_traversal(this->root, 1);
        return depth;
    }

    Dict<TKey, TValue>() {
        this->root = nullptr;
        this->size = 0;
    }

    ~Dict() {
        if (this->size != 0)
            this->clear();
    }

    class StopTraversal : public std::exception {
    };
};

#endif //LB4_DICT_H
