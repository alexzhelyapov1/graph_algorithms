#include <iostream>
#include <string>
#include "SplayTree.h"

int main() {

    Tree<int>* my_tree = new Tree<int>();
    my_tree->Insert(3);
    my_tree->Insert(7);
    my_tree->Insert(6);
    my_tree->Insert(4);
    my_tree->Insert(8);
    my_tree->root_ = my_tree->root_->Find(4);
    auto t = my_tree->Split(4);


    out.open("/home/alex/graph_algorithms/splay_tree/GV.txt");
    if (!out.is_open()) {
        throw std::runtime_error("ERROR! Can't open file\n");
    }

    out << "digraph graphname {\n";

    // my_tree.Delete(4);

    // root->GraphVizPrint(out);
    // my_tree->root_->GraphVizPrint(out);
    // my_tree->root_->GraphVizPrint(out);

    // if (t.first != nullptr)
    //     t.first->GraphVizPrint(out, "red");
    // if (t.second != nullptr)
    //     t.second->GraphVizPrint(out, "red");


    Node<int>* new_root = Tree<int>::Merge(t.first, t.second);
    new_root->GraphVizPrint(out);
    // if (my_tree.root_ != nullptr)
    //     my_tree.root_->GraphVizPrint(out);
    // my_tree->root_->GraphVizPrint(out, "green");
    delete my_tree;
    out << "}";
    out.close();

} // dot -v -Tpng -o GV.png GV.txt; code GV.png


