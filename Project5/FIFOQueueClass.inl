#include "LinkedNodeClass.h"
#include <iostream>
#include "FIFOQueueClass.h"

using namespace std;


//Author: Yi Zhou
//Date:04/15/2022
//FIFOQueueClass functions definition

template <class T>
FIFOQueueClass<T>::FIFOQueueClass() {
    head = 0;
    tail = 0;
}
  
template <class T>
FIFOQueueClass<T>::~FIFOQueueClass() {
    clear();
}
 
template <class T>
void FIFOQueueClass<T>::enqueue( 
    const T &newItem 
) {
    //head and tail point to this new node if empty
    LinkedNodeClass<T> *nodeToEnqueue;
    if (head == 0) {
        nodeToEnqueue = new LinkedNodeClass<T>(0, newItem, 0);
        head = nodeToEnqueue;
        tail = nodeToEnqueue;
    }
    //otherwise the new node becomes the new head
    else {
        nodeToEnqueue = new LinkedNodeClass<T>(0, newItem, head);
        nodeToEnqueue->setBeforeAndAfterPointers();
        head = nodeToEnqueue;
    }
}
  
template <class T>
bool FIFOQueueClass<T>::dequeue( 
    T &outItem 
) {
    //return false if queue has no element
    if (head == 0) {
        return false;
    }
    //otherwise return true
    //if queue has one element, output value and delete it
    if (getNumElems() == 1) {
        outItem = tail->getValue();
        clear();
    }
    //if more than one element, output value, delete tail, 
    //and set up new tail
    else {
        //extract value
        outItem = tail->getValue();
        //move to new tail
        tail = tail->getPrev();
        //delete the old tail
        delete tail->getNext();
        //set up the new tail appropriately
        tail->setNextPointerToNull();
    }
    return true;
}
  
template <class T>
void FIFOQueueClass<T>::print() const {
    //print from tail to head
    //will result in a white space after the last print, but I think it's ok
    LinkedNodeClass<T> *nodeToPrint = tail;
    while (nodeToPrint != 0) {
        cout << nodeToPrint->getValue() << " ";
        nodeToPrint = nodeToPrint->getPrev();
    }
    cout << endl;
}

template <class T>
int FIFOQueueClass<T>::getNumElems() const {
    //exactly the same function as the one in SortedListClass
    LinkedNodeClass<T> *tempNode = head;
    int count = 0;
    while (tempNode != 0) {
        tempNode = tempNode->getNext();
        count++;
    }
    return count;
}

template <class T>
void FIFOQueueClass<T>::clear() {
    //also the same
    LinkedNodeClass<T> *tempNode = head;
    LinkedNodeClass<T> *nodeToDelete = head;
    while (tempNode != 0) {
        tempNode = tempNode->getNext();
        delete nodeToDelete;
        nodeToDelete = tempNode;
    }
    head = 0;
    tail = 0;
}