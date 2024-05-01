#include <iostream>
#include <string>
#include "SplayTree.h"

template <typename T>
class Test 
{
  public:
    Test(T data) {
        data_ = data;
        std::cout << data_ << std::endl;
    }

  private:
    std::string data_;
};

int main() {
    std::cout << "Hello\n";
    auto t = new Test<std::string>("hihihi");
    // t->Print();
}