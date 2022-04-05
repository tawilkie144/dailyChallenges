//An XOR linked list is a more memory efficient doubly linked list. Instead of each node holding next and prev fields,
//it holds a field named both, which is an XOR of the next node and the previous node. Implement an XOR linked list;
//it has an add(element) which adds the element to the end, and a get(index) which returns the node at index.

//If using a language that has no pointers (such as Python), you can assume you have access to get_pointer
//and dereference_pointer functions that converts between nodes and memory addresses.


#include <iostream>
#include <cstdint>

#include "XorList.h"


int main(int argc, char **argv){
    XorList<int> *list = new XorList<int>(1);
    list->Add(2);
    list->Add(3);
    list->Add(4);
    list->Add(5);

    for(int i = 0; i < 5; i++){
        std::cout << list->Get(i) << " ";
    }
    std::cout << std::endl;

    delete list;

    return 0;
}