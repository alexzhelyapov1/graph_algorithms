#include <iostream>
#include <string>
#include "SplayTree.h"



int main() {
    Node<int> a(6);
    Node<int>* root = &a;
    Node<int> b(5, &a);
    Node<int> c(7, &a);
    Node<int> d(8, &b);

    root = b.RightRotate();

    std::ofstream out("/home/alex/graph_algorithms/splay_tree/GV.txt");
    if (!out.is_open()) {
        throw std::runtime_error("ERROR! Can't open file\n");
    }

    out << "digraph graphname {\n";


    // root->GraphVizPrint(out);
    root->GraphVizPrint(out);

    out << "}";
    out.close();
} // dot -v -Tpng -o GV.png GV.txt; code GV.png