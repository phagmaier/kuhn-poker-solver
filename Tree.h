//
// Created by Parker Hagmaier on 2/28/24.
//

#ifndef FINAL_TREE_H
#define FINAL_TREE_H
#include "Node.h"
#include <string>
#include <iostream>

class Tree {
public:
    Tree();
    ~Tree();
    void delete_nodes(Node *node);
    void make_tree(Node *node);
    void print_tree();
    void print_helper(Node *node);
    void calc_regret(Node *node);
    void gen_regrets(Node *l, Node *r);
    void run_cfrm();
    void print_regrets(Node *node);
    void update_strategy(Node *l, Node *r);
    void normalize(Node *l, Node *r);
    void print_strats(Node *node);
    void get_final_strat(Node *node_l, Node *node_r);
private:
    Node *left;
    Node *right;
};


#endif //FINAL_TREE_H
