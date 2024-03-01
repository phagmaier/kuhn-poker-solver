//
// Created by Parker Hagmaier on 2/28/24.
//

#include "Node.h"


Node::Node(bool bet, std::string name, Node *parent): bet{bet}, name{name}, parent{parent} {
    left = nullptr;
    right = nullptr;
    calc_potsize();
    for (int i=0; i<3;++i){
        strat[i] = 0.5;
        regrets[i] = 0.0;
        strat_sum[i] =0;
        for (int x=0; x<3;++x){
            ev[i][x] = 0.0;
        }
    }
}

Node::Node(bool bet, std::string name) : bet{bet}, name{name} {
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    potsize = 1;
    for (int i=0; i<3;++i){
        strat[i] = 0.5;
        regrets[i] = 0.0;
        strat_sum[i]=0;
        for (int x=0; x<3;++x){
            ev[i][x] = 0;
        }
    }
}

bool Node::is_p1() {
    return name.length() % 2 == 1;
}

bool Node::bet_or_check() const {
    return bet;
}

bool Node::is_leaf() {
    return left == nullptr;
}

void Node::leaf_ev() {
    if (parent->bet_or_check() && !bet){
        for (int i=0;i<3;++i){
            for (int x=0;x<3;++x){
                if (i!=x){
                ev[i][x] = -1;}
            }
        }
    }
    else{
        for (int i=0;i<3;++i){
            for (int x=0;x<3;++x){
                if (i!=x){
                    ev[i][x] = i>x ? potsize : -potsize;}
            }
        }

    }
}

void Node::calc_potsize() {
    std::string parent_name = parent->get_name();
    int length = parent_name.length() -1;
    potsize = parent_name[length] == 'b' && parent_name[parent_name.length()-1] == 'b'
    ? 2:1;
}

std::string Node::get_name() {
    return name;
}


void Node::make_children() {
    left = new Node(false, name+'c', this);
    right = new Node(true, name+'b', this);
}

Node *Node::get_left() {
    return left;
}

Node *Node::get_right() {
    return right;
}

Node *Node::get_parent() {
    return parent;
}


double Node::get_ev(int card1, int card2) {
    return ev[card1][card2];
}

double Node::get_strat(int card1) {
    return strat[card1];
}


bool Node::is_terminal() {
    if (!parent){
        return false;
    }
    return !(!parent->bet_or_check() && bet);
}

void Node::print_node() {
    std::cout << name << "\n";
}


void Node::gen_regrets() {
    double l;
    double r;
    double total;

    for (int card1=0;card1<3;++card1){
        for (int card2=0; card2<3; ++card2){
            if (card1!=card2) {
                l = left->get_ev(card1, card2);
                r = right->get_ev(card1, card2);
                total = l * left->get_strat(card1) + r * right->get_strat(card1);
                ev[card2][card1] = -total;
                left->add_regret(card1, (l - total) * get_strat(card2));
                right->add_regret(card1, (r - total) * get_strat(card2));
            }
        }
    }

}

void Node::add_regret(int index, double val) {
    regrets[index] += val;
}


void Node::print_regret() {
    print_node();
    for(int i=0;i<3;++i){
        std::cout << regrets[i] << " ";
    }
    std::cout << "\n";
}

void Node::print_ev() {
    std::cout << "EXPECTED VALUE OF NODE: " << name;
    for (int i=0;i<3;++i){
        std::cout << "\n";
        for (int x=0;x<3;++x){
            std::cout << ev[i][x] << " ,";
        }
    }
    std::cout << "\n";
}

void Node::update_strat(int index, double new_strat) {
    strat[index] = new_strat;
    strat_sum[index] += new_strat;
}

void Node::set_strat(int index, double new_strat) {
    strat[index] = new_strat;
}

double Node::get_regret(int index) {
    return regrets[index];
}

void Node::print_strat() {
    std::cout << "The strategy for: " << name << ": ";
    for (int i=0;i<3;++i){

        std::cout << get_strat(i) << ", ";
    }
    std::cout << "\n";
}

double Node::get_strat_sum(int index) {
    return strat_sum[index];
}


