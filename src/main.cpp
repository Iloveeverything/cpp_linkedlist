#include "../include/linked_list.hpp"
#include <iostream>

int main() {
    LinkedList<int> list;
    
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    for (int val : list) {
        std::cout << val << "\n";
    }
    
    list.reverse();
    std::cout << list << "\n";

    LinkedList<int> copy = list;
    copy.push_back(99);
    std::cout << "original: " << list << "\n";
    std::cout << "copy: " << copy << "\n";
    
    return 0;
}