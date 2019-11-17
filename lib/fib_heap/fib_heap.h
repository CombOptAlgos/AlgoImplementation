#ifndef FIB_HEAP_FIB_HEAP_H
#define FIB_HEAP_FIB_HEAP_H

#include <iostream>
#include <math.h>
#include <queue>

using namespace std;

template <class Key, class Val>
class fib_heap {

private:
    typedef struct node {
        Key key;
        Val val;
        bool root;
        int psi;
        int degree;
        struct node* parent;
        vector<struct node*> childlen;
    } Node;

    vector<Node*> b;

    Node *generate_node(Key key, Val val) {
        Node node;
        node->key = key;
        node->val = val;
        node->root = false;
        node->psi = 0;
        node->degree = 0;
        node->parent = nullptr;
        return &node;
    };

    void plant(Node* node) {
        int node_degree = node->degree;
        Node *r = b[node_degree];
        if (r!=nullptr && r->root && r!=node && node_degree==r->degree) {
            if (r->key<=node->key) {
                r->children.push_back(node);
                r->degree++;
                node->parent = r;
                plant(r);
            } else {
                node->children.push_back(r);
                node->root = true;
                node->degree++;
                r->parent = node;
                r->root = false;
            }
        } else
            b[node_degree] = node;
    };

    Node* scan() {
        int min = b[0]->key;
        Node *argmin = b[0];
        for (int i=1; i<b.size(); i++) {
            if (b[i]!=nullptr && b[i]->key<min) {
                min = b[i]->key;
                argmin = b[i];
            }
        }
        return argmin;
    };

    void del(Node* node) {
        if (node->root) {
            for (int i=0; i<node->children.size(); i++) {
                node->children[i]->root=true;
                node->children[i]->parent=nullptr;
            }
        } else {
            for (int i=0; i<node->children.size(); i++) {
                node->children[i]->parent = node->parent;
                node->parent->children.push_back(node->children[i]);
            }
            node->parent->degree += node->children.size();
        }
    };

    Node *find_longest_path_and_update_psi(
            Node *node, vector<Node*> node_list) {
        node_list.push_back(node);
        if (node->parent->psi==0 || node->parent->root) {
            node->root = true;
            auto iter = find(node->parent->children.begin(),
                    node->parent->children.end(), node);
            node->parent->children.erase(iter);
            node->parent->degree--;
            node->list.push_back(node->parent);
            node->parent = nullptr;
            return node_list;
        } else {
            node->root = true;
            node->parent->psi = 0;
            auto iter = find(node->parent->children.begin(),
                    node->parent->children.end(), node);
            node->parent->children.erase(iter);
            Node *tmp = node->parent;
            node->parent = nullptr;
            find_longest_path_and_update_psi(tmp);
        }
    };

    Node *search_and_update_node_cost(Key key, Val val) {
        for (int i=0; i<b.size(); i++) {
            if (b[i]->root) {
                if (b[i]->val==val)
                    return b[i];
                Node *tmp = b[i];
                queue<Node*> search_queue;
                while (true) {
                    for (int i=0; i<tmp->children.size(); i++) {
                        if (tmp->children[i]->val==val)
                            return tmp->children[i];
                        else
                            search_queue.push(tmp->children[i]);
                    }
                    if (search_queue.front()!=nullptr) {
                        tmp = search_queue.front();
                        search_queue.pop();
                    } else
                        break;
                }
                throw;
            }
        }
    };

public:
    fib_heap(int N) {
        int max = floor(2*log2(N));
        b.resize(max);
        for (int i=0; i<max; i++)
            b[i] = nullptr;
    };

    ~fib_heap() {};

    void insert(Key key, Val val) {
        Node *node = generate_node(key, val);
        plant(node);
    };

    Val deletemin() {
        Node *argmin = scan();
        del(argmin);
        for (int i=0; i<argmin->children.size(); i++)
            plant(argmin->children[i]);
        argmin = nullptr;
        delete argmin;
    };

    void decreasekey(Key key, Val val) {
        Node *updated = search_and_update_node_cost(key, val);
        vector<Node*> longest_path = 
            find_longest_path_and_update_psi(updated);
        for(int i=0; i<longest_path.size(); i++)
            plant(longest_path[i]);
    };

};
#endif // FIB_HEAP_FIB_HEAP_H
