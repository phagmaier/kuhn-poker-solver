#include <iostream>
#include "Node.h"
#include <string>
#include "Tree.h"


void func(){
    Tree tree = Tree();
    tree.print_tree();
}

int main() {
    Tree tree = Tree();
    tree.run_cfrm();

    return 0;
}
