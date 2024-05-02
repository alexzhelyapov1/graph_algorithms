#include <iostream>
#include <string>
#include "SplayTree.h"



int main() {
    Node<int> a(6);
    Node<int> b(5, &a);
    Node<int> c(7, &a);
    Node<int> d(8, &b);

    a.RightRotate();

    std::ofstream out("/home/alex/graph_algorithms/splay_tree/GV.txt");
    if (!out.is_open()) {
        throw std::runtime_error("ERROR! Can't open file\n");
    }

    out << "digraph graphname {\n";


    b.GraphVizPrint(out);

    out << "}";
    out.close();
}