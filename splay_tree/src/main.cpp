#include <iostream>
#include "SplayTree.h"

int main() {
    std::cout << "Hello\n";
    Test<std::string>* t = new Test<std::string>("hihihi");
    t->Print();
}