#include <iostream>
#include "Node.h"
#include <string>
#include "Tree.h"

//my destuructor in node actually won't work
// need to change that to make it recursive and delete the very last node first

void func(){
    Tree tree = Tree();
    tree.print_tree();
}

int main() {
    Tree tree = Tree();
    tree.run_cfrm();
    //std::cout << "Hello world\n";

    return 0;
}
