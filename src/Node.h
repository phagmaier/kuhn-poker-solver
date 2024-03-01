#ifndef FINAL_NODE_H
#define FINAL_NODE_H
#include <iostream>
#include <string>
#include <thread>

class Node {
public:
    Node(bool bet, std::string name);
    double get_ev(int card1, int card2);
    inline bool is_leaf() {return left == nullptr;}
    inline bool is_p1() {return name.length() % 2 == 1;}
    inline bool bet_or_check() const {return bet;}
    inline Node *get_left() {return left;}
    inline Node *get_right() {return right;};
    inline Node *get_parent() {return parent;}
    inline std::string get_name() {return name;}    
    void make_children();
    inline double get_strat(int card1) {return strat[card1];}
    bool is_terminal();
    void print_node();
    inline void add_regret(int index, double val) {regrets[index] += val;} 
    void print_regret();
    void gen_regrets();
    void print_ev();
    void update_strat(int index, double new_strat); // also increases the strat sum
    inline void set_strat(int index, double new_strat) {strat[index] = new_strat;}
    inline double get_regret(int index) {return regrets[index];}
    void print_strat();
    inline double get_strat_sum(int index) {return strat_sum[index];}


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
