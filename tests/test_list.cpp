#include "../include/linked_list.hpp"
#include <iostream>
#include <cassert>

int main(){

    LinkedList<int> list;


    //push and size
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    assert(list.size()==3);
    assert(list.at(0)==1);
    assert(list.at(1)==2);
    assert(list.at(2)==3);
    std::cout<<"push/size test passed \n";

    //push_front
    list.push_front(0);
    assert(list.at(0)==0);
    assert(list.size()==4);
    std::cout<<"push_front test passed\n";

    //test pop_front and pop_back
    list.pop_front();
    assert(list.at(0)==1);
    list.pop_back();
    assert(list.size()==2);
    std::cout<<"pop test passed\n";

    //test insert
    list.insert(1,99);
    assert(list.at(1)==99);
    assert(list.size()==3);
    std::cout<<"insert test passed\n";

    //test remove
    list.remove(99);
    assert(list.contains(99)==false);
    assert(list.size()==2);
    std::cout<<"remove tests passed\n";

    //test modify copy
    LinkedList<int> copy = list;
    copy.push_back(49);
    assert(list.size()==2); //test original size stays the same
    assert(copy.size()==3);//test copy size increased by one element
    std::cout<<"copy modify test passed\n";

    //test move
    LinkedList<int> moved = std::move(list);
    assert(moved.size()==2);
    assert(list.empty()); //original list should be empty after move
    std::cout<<"move test passed\n";
    
    //test iterator
    int sum=0;
    for (int val : moved){
        sum+= val;
    }
    assert(sum == 3);
    std::cout<< "iterator test passed\n";
    
    std::cout << "all tests passed!";
    return 0;

}