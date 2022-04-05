//An XOR linked list is a more memory efficient doubly linked list. Instead of each node holding next and prev fields,
//it holds a field named both, which is an XOR of the next node and the previous node. Implement an XOR linked list;
//it has an add(element) which adds the element to the end, and a get(index) which returns the node at index.

//If using a language that has no pointers (such as Python), you can assume you have access to get_pointer
//and dereference_pointer functions that converts between nodes and memory addresses.


#ifndef XORLIST_H
#define XORLIST_H

#include <stdexcept>
#include <iterator>
#include <cstddef>

//-----------------------------
//      class definitions
//-----------------------------

template <typename T>
class XorListNode{
public:
    XorListNode(T data_in): data_(data_in){}
    XorListNode<T> *GetNext(XorListNode<T> *previous);
    XorListNode<T> *GetPrevious(XorListNode<T> *next);

    inline void SetNeighbors(XorListNode *new_neighbors){both_ = new_neighbors;}
    inline T &GetData(){return data_;}
    inline XorListNode<T> *&GetBoth() {return both_;}
    inline T operator*() {return data_;}

private:
    T data_;
    XorListNode<T> *both_;
};

template <typename T>
class XorList{
public:
    XorList(T data);
    ~XorList();

    size_t Add(T data_in);
    T &Get(size_t index);
    inline size_t Size(){return size_;}

private:
    XorListNode<T> *GetLast();

    XorListNode<T> *head_;
    size_t size_;
};

//----------------------------
//     method definitions
//----------------------------

//----------------------------
//      Node definitions
//----------------------------

template <typename T>
XorListNode<T> *XorListNode<T>::GetNext(XorListNode<T> *previous){
    return (XorListNode<T> *)((uintptr_t)this->both_ ^ (uintptr_t)previous);
}

template <typename T>
XorListNode<T> *XorListNode<T>::GetPrevious(XorListNode<T> *next){
    return (XorListNode<T> *)((uintptr_t)next ^ (uintptr_t)this->both_);
}

//----------------------------
//     List definitions
//----------------------------

template <typename T>
XorList<T>::XorList(T data){
    this->head_ = new XorListNode<T>(data);
    head_->SetNeighbors(nullptr);
    size_ = 1;
}

template <typename T>
XorList<T>::~XorList(){
    XorListNode<T> *ptr = this->head_;
    XorListNode<T> *previous = nullptr;
    XorListNode<T> *next;
    for(int i = 0; i < size_; i++){
        next = ptr->GetNext(previous);
        previous = ptr;
        ptr = next;
        delete previous;
    }
}

template<typename T>
XorListNode<T> *XorList<T>::GetLast(){
    XorListNode<T> *cur = this->head_;
    XorListNode<T> *previous = nullptr;
    XorListNode<T> *next;

    while((next = cur->GetNext(previous)) != nullptr){
        previous = cur;
        cur = next;
    }

    return cur;
}

template <typename T>
size_t XorList<T>::Add(T data_in){
    XorListNode<T> *new_node = new XorListNode<T>(data_in);
    XorListNode<T> *last = GetLast();

    new_node->SetNeighbors((XorListNode<T> *)((uintptr_t)last ^ 0));
    last->SetNeighbors((XorListNode<T> *)((uintptr_t)last->GetBoth() ^ (uintptr_t)new_node));

    return ++size_;
}

template <typename T>
T &XorList<T>::Get(size_t index){
    
    if(index+1 > this->size_){
        throw std::out_of_range(std::string("Desired index is out of range of the list. Provided index: ").append(std::to_string(index)).append(std::string(" - Size of list: ")).append(std::to_string(size_)));
    }
    XorListNode<T> *ptr;
    XorListNode<T> *previous = nullptr;
    XorListNode<T> *next;
    for(int i = 0; i <= index; i++){
        if(i == 0){
            ptr = this->head_;
        }else{
            ptr = next;
        }
        next = ptr->GetNext(previous);
        previous = ptr;
    }

    return ptr->GetData();
}

#endif