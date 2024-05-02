#include <iostream>
#include <string>
#include "SplayTree.h"



int main() {
    Node<int> a(6);
    Node<int>* root = &a;
    Node<int> b(5, &a);
    Node<int> c(7, &a);
    Node<int> d(8, &b);

    Tree<int> my_tree;
    my_tree.Insert(3);
    my_tree.Insert(7);
    my_tree.Insert(6);
    my_tree.Insert(4);
    // my_tree.Insert(8);

    // root = a.RightRotate();
    // root = d.Splay();

    std::ofstream out("/home/alex/graph_algorithms/splay_tree/GV.txt");
    if (!out.is_open()) {
        throw std::runtime_error("ERROR! Can't open file\n");
    }

    out << "digraph graphname {\n";


    // root->GraphVizPrint(out);
    my_tree.root_->GraphVizPrint(out);

    out << "}";
    out.close();
} // dot -v -Tpng -o GV.png GV.txt; code GV.png