//
// Created by Parker Hagmaier on 2/28/24.
//

#ifndef FINAL_NODE_H
#define FINAL_NODE_H
#include <iostream>
#include <string>
#include <thread>

class Node {
public:
    Node(bool bet, std::string name);
    double get_ev(int card1, int card2);
    bool is_leaf();
    bool is_p1();
    bool bet_or_check() const;
    Node *get_left();
    Node *get_right();
    Node *get_parent();
    std::string get_name();
    void make_children();
    double get_strat(int card1);
    bool is_terminal();
    void print_node();
    void add_regret(int index, double val); //adds to regrets
    void print_regret();
    void gen_regrets();
    void print_ev();
    void update_strat(int index, double new_strat); // also increases the strat sum
    void set_strat(int index, double new_strat);
    double get_regret(int index);
    void print_strat();
    double get_strat_sum(int index);
    void leaf_ev();
private:

    Node(bool bet, std::string name, Node *node);
    bool bet;
    std::string name;
    Node *parent;
    Node *left;
    Node *right;
    double strat[3];
    double regrets[3];
    double strat_sum[3];
    double ev[3][3];
    void calc_potsize();
    double potsize;

};


#endif //FINAL_NODE_H
