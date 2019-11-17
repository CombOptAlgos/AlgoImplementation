#ifndef FIB_HEAP_FIB_HEAP_H
#define FIB_HEAP_FIB_HEAP_H

#include <iostream>
#include <math.h>

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

    Node* argmin() {
        /* implement here */
    };

    void find_longest_path_and_update_psi() {
        /* implement here */
    };

    void del(Node* node) {
        /* implement here */
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
        /* implement here */
    };

    void decreasekey(Key key, Val val) {
        /* imploement here */
    };

};
 
#endif // FIB_HEAP_FIB_HEAP_H
