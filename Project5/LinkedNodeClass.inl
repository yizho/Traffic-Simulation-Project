#include <iostream>
#include "LinkedNodeClass.h"

using namespace std;

//Author: Yi Zhou
//Date:04/15/2022
//LinkedNodeClass functions declaration

template <class T>
LinkedNodeClass<T>::LinkedNodeClass(  
    LinkedNodeClass<T> *inPrev, //Address of node that comes before this one
    const T &inVal,        //Value to be contained in this node  
    LinkedNodeClass<T> *inNext  //Address of node that comes after this one  
) {
    prevNode = inPrev;
    nextNode = inNext;
    nodeVal = inVal;
}

template <class T>
T LinkedNodeClass<T>::getValue() const {
    return nodeVal;
}

template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getNext() const {
    return nextNode;
}

template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getPrev() const {
    return prevNode;
}

template <class T>
void LinkedNodeClass<T>::setNextPointerToNull() {
    nextNode = 0;
}

template <class T>
void LinkedNodeClass<T>::setPreviousPointerToNull() {
    prevNode = 0;
}

template <class T>
void LinkedNodeClass<T>::setBeforeAndAfterPointers() {
    //if prevNode exists, set the nextNode of the prevNode to this node
    if (prevNode != 0) {
        prevNode->nextNode = this;
    }
    //if nextNode exists, set the prevNode of the nextNode to this node
    if (nextNode != 0) {
        nextNode->prevNode = this;
    }
}