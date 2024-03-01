//
// Created by Parker Hagmaier on 2/28/24.
//

#include "Tree.h"

Tree::Tree() {
    left = new Node(false, "c");
    right = new Node(true, "b");
    make_tree(left);
    make_tree(right);
}
void Tree::make_tree(Node *node) {
    if (!node->is_terminal()){
        node->make_children();
        make_tree(node->get_right());
        make_tree(node->get_left());
    }
}

void Tree::print_tree() {
    print_helper(left);
    print_helper(right);
}

void Tree::print_helper(Node *node) {
    if (node){
        node->print_node();
        print_helper(node->get_left());
        print_helper(node->get_right());
    }
}

Tree::~Tree() {
    delete_nodes(left);
    delete_nodes(right);
}

void Tree::delete_nodes(Node *node) {
    if (node->get_left()){
        delete_nodes(node->get_left());
        delete_nodes(node->get_right());
    }
    delete node;
}

void Tree::gen_regrets(Node *l, Node *r) {
    int card1;
    int card2;
    double actual_l;
    double actual_r;
    double total;
    for (card1=0; card1<3; ++card1){
        for (card2=0; card2<3;++card2){
            if (card1!=card2){
                actual_l = l->get_ev(card1,card2);
                actual_r = r->get_ev(card1,card2);
                total = actual_l * l->get_strat(card1) + actual_r * r->get_strat(card1);
                l->add_regret(card1, actual_l-total);
                r->add_regret(card1, actual_r-total);
                }

            }
        }

    }


//almost perfect but something is a tiny bit wrong with cc
void Tree::run_cfrm() {
    int iterations = 10000;
    for (int i=0;i<iterations;++i) {
        calc_regret(left);
        calc_regret(right);
        gen_regrets(left, right);
        update_strategy(left,right);
        //std::cout << "\nREGRETS:\n\n";
        //print_regrets(left);
        //print_regrets(right);
    }
    //print_strats(left);
    //print_strats(right);
    std::cout << "\n";
    get_final_strat(left,right);
    print_strats(left);
    print_strats(right);
}


void Tree::calc_regret(Node *node) {
   /*
    if (node->get_left()){
        calc_regret(node->get_left());
        calc_regret(node->get_right());
    }
    if (node->is_leaf()){
        node->calc_ev();
    }
    else{
        //node->calc_ev();
        node->gen_regrets();
    }
     */
    if (node->get_left()){
        calc_regret(node->get_left());
        calc_regret(node->get_right());
    }
    if (node->is_leaf()){
        node->leaf_ev();
    }
    else{
        //node->calc_ev();
        node->gen_regrets();
    }
}

void Tree::print_regrets(Node *node) {
    if (node->get_left()){
        print_regrets(node->get_left());
        print_regrets(node->get_right());
    }
    node->print_regret();
}


void Tree::normalize(Node *l, Node *r) {
    for (int i=0;i<3;++i) {
        double temp_l = l->get_regret(i) > 0 ? l->get_regret(i) : 0;
        double temp_r = r->get_regret(i) > 0 ? r->get_regret(i) : 0;
        double  total = temp_l + temp_r;
        if (!total){
            l->update_strat(i,.5);
            r->update_strat(i,.5);
        }
        else{
            l->update_strat(i, temp_l/total);
            r->update_strat(i, temp_r/total);
        }
    }
}

void Tree::print_strats(Node *node) {
    if (node){
        print_strats(node->get_left());
        print_strats(node->get_right());
        node->print_strat();
    }
}

void Tree::get_final_strat(Node *node_l, Node *node_r) {
    if (node_l){

        get_final_strat(node_l->get_left(), node_l->get_right());
        get_final_strat(node_r->get_left(), node_r->get_right());
        double l;
        double r;
        double total;
        for (int i=0; i<3; ++i) {
            l = node_l->get_strat_sum(i) > 0 ? node_l->get_strat_sum(i) : 0;
            r = node_r->get_strat_sum(i) > 0 ? node_r->get_strat_sum(i) : 0;
            total = l+r;
            if (!total){
                node_l->set_strat(i, 0.5);
                node_r->set_strat(i,0.5);
            }
            else{
                node_l->set_strat(i, l/total);
                node_r->set_strat(i,r/total);
            }

        }
    }
}

//think this doesn't do check check fix this think because
//it doesn't normalize it
void Tree::update_strategy(Node *l, Node *r) {
        normalize(l, r);
        if (l->get_left()){
            update_strategy(l->get_left(),l->get_right());}
        if (r->get_left()){
            update_strategy(r->get_left(), r->get_right());}

}
