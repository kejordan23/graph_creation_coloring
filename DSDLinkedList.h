// Project 2: Asymptotic Graph Creation
// Author: Kylie Jordan
//
// DSDLinkedList.h
//
// This header file declares and defines the DSDLinkedList class constructors and functions.
// The Node class and its implementation is also included in this file
// Referenced from Kylie Jordan's code created during CS2341 Fall2020

#ifndef INC_20F_AUTO_IDX_DSDLINKEDLIST_H
#define INC_20F_AUTO_IDX_DSDLINKEDLIST_H

#include <iostream>
#include <fstream>

using namespace std;

//templated Node class constructs a Node with a pointer to the next and previous node
template <typename T>
class Node{
public:
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node(T& val = T(), Node* n = nullptr, Node* d = nullptr): data(val), next(n), prev(d){};
};

//templated DSDLinkedList class constructs a list of Node objects with a front Node and an end Node
template <typename T>
class DSDLinkedList{
    private:
        Node<T>* front;
        Node<T>* end;
        int size;
    public:
        DSDLinkedList(){            //default constructor with definition inlined
            front = nullptr;
            end = nullptr;
            size = 0;
        };
        ~DSDLinkedList(){clear();};
        DSDLinkedList(const DSDLinkedList<T>&);
        DSDLinkedList<T>& operator=(const DSDLinkedList<T>&);
        bool empty();
        T& getElement(int);
        int getSize();
        void insertAtFront(T&);
        void insertAtEnd(T&);
        void insertAt(int, T&);
        void remove(int);
        bool contains(T&);
        void clear();
        void print(ofstream&);
};

//copy constructor
template <typename T>
DSDLinkedList<T>::DSDLinkedList(const DSDLinkedList<T>& list2){
    front = nullptr;
    end = nullptr;
    size = 0;
    Node<T>* curr2 = list2.front;
    while(curr2 != nullptr){
        insertAtEnd(curr2->data);
        curr2 = curr2->next;
    }
}
//overloaded copy assignment operator
template <typename T>
DSDLinkedList<T>& DSDLinkedList<T>::operator=(const DSDLinkedList<T>& list2){
    if(this == &list2)
        return *this;
    clear();                            //frees memory in this list before assigning new Nodes
    Node<T>* curr2 = list2.front;
    while(curr2 != nullptr){
        insertAtEnd(curr2->data);
        curr2 = curr2->next;
    }
    return *this;
}
template <typename T>
bool DSDLinkedList<T>::empty(){
    if (size ==0)
        return true;
    else
        return false;
}
template <typename T>
T& DSDLinkedList<T>::getElement(int loc){
    Node<T> *curr = front;
    for (int i = 0; (i < loc) && (curr->next != nullptr); i++) {
        curr = curr->next;
    }
    return curr->data;
}
template <typename T>
int DSDLinkedList<T>::getSize(){
    return size;
}
//insert functions at front, end, and a given location
template <typename T>
void DSDLinkedList<T>::insertAtFront(T& val){
    Node<T>* temp = new Node<T>(val);
    if(empty()){
        front = end = temp;
        size++;
    }
    else {
        Node<T>* curr = front;
        curr->prev = temp;
        temp->next = curr;
        front = temp;
        end = curr;
        size++;
    }
}
template <typename T>
void DSDLinkedList<T>::insertAtEnd(T& elem){
    Node<T>* temp = new Node<T>(elem);
    if(size == 0)
        front = end = temp;
    else{
        Node<T>* curr = end;
        while (curr->next != nullptr){
            curr = curr->next;
        }
        curr->next = temp;
        temp->prev = curr;
        end = temp;
    }
    size++;
}
template <typename T>
void DSDLinkedList<T>::insertAt(int loc, T& val){    //starts from front Node and loops to find location before inserting
    if(size == 0){
        insertAtFront(val);
    }
    else if (loc>0 && loc<size){
        Node<T> *temp = new Node<T>(val);
        Node<T> *curr = front;
        for (int i = 0; (i < loc-1) && (curr->next != nullptr); i++) {
            curr = curr->next;
        }
        temp->next = curr->next;
        curr->next->prev = temp;
        curr->next = temp;
        temp->prev = curr;
        size++;
    }
}
//function to remove a node from the list
template <typename T>
void DSDLinkedList<T>::remove(int loc){
    Node<T> *curr = front;
    for (int i = 0; (i < loc) && (curr->next != nullptr); i++) {
        curr = curr->next;
    }
    if(curr->next == nullptr)
        end = curr->prev;
    else
        curr->next->prev = curr->prev;
    if(curr->prev == nullptr)
        front = curr->next;
    else
        curr->prev->next = curr->next;
    delete curr;                            //frees the pointer being removed
    size--;
}
template <typename T>
bool DSDLinkedList<T>::contains(T& elem){
    bool cnt = false;
    for(int i = 0; i< size; i++){
        if(getElement(i) == elem){
            cnt = true;
            break;
        }
    }
    return cnt;
}
//function to free memory in the list
template <typename T>
void DSDLinkedList<T>::clear(){
    Node<T>* temp;
    Node<T>* tempNext;
    temp = front;
    while(temp != nullptr){
        tempNext = temp->next;
        delete temp;
        temp = tempNext;
    }
    front = nullptr;                        //re-initializes the list
    end = nullptr;
    size = 0;
}
template <typename T>
void DSDLinkedList<T>::print(ofstream& out){
    Node<T>* curr = front;
    for(int i =0; i<size; i++){
        out<< curr->data;
        if(i != size-1)
            out<<", ";
        curr = curr->next;
    }
}

#endif //INC_20F_AUTO_IDX_DSDLINKEDLIST_H
