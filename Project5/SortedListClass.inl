#include <iostream>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"

using namespace std;

//Author: Yi Zhou
//Date:04/15/2022
//SortedListClass functions definitions
template <class T>
SortedListClass<T>::SortedListClass() {
    head = 0;
    tail = 0;
}

template <class T>
SortedListClass<T>::SortedListClass( 
    const SortedListClass<T> &rhs 
) {
    head = 0;
    tail = 0;
    //go over the rhs list
    //copies the current node, and go to the next node.
    LinkedNodeClass<T> *tempNode = rhs.head;
    while (tempNode != 0) {
        this->insertValue(tempNode->getValue());
        tempNode = tempNode->getNext();
    }
}
  
template <class T>
SortedListClass<T>::~SortedListClass() {
    clear();
}
 
template <class T>
void SortedListClass<T>::clear() {
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
  
template <class T>
void SortedListClass<T>::insertValue( 
    const T &valToInsert
) {
    LinkedNodeClass<T> *nodeToInsert = 0;
    //if list is empty, head and tail are both pointing to the new node.
    if (head == 0) {
        nodeToInsert = new LinkedNodeClass<T>(0, valToInsert, 0);
        head = nodeToInsert;
        tail = nodeToInsert;
        return;
    }
    //if the inserting value is smaller than head
    if (valToInsert < head->getValue()) {
        nodeToInsert = new LinkedNodeClass<T>(0, valToInsert, head);
        nodeToInsert->setBeforeAndAfterPointers();
        head = nodeToInsert;
    }
    //if the value is greater than or equal to tail
    else if (valToInsert >= tail->getValue()) {
        nodeToInsert = new LinkedNodeClass<T>(tail, valToInsert, 0);
        nodeToInsert->setBeforeAndAfterPointers();
        tail = nodeToInsert;
    }
    //if the value is somewhere in the middle of the list
    else {
        nodeToInsert = head;
        while (valToInsert >= nodeToInsert->getValue()) {
            nodeToInsert = nodeToInsert->getNext();
        }
        nodeToInsert = new LinkedNodeClass<T>(nodeToInsert->getPrev(),
        valToInsert, nodeToInsert);
        nodeToInsert->setBeforeAndAfterPointers();
    }
    return;
}


  
template <class T>
void SortedListClass<T>::printForward() const {
    cout << "Forward List Contents Follow:" << endl;
    LinkedNodeClass<T> *nodeToPrint = head;
    while (nodeToPrint != 0) {
        cout << "  " << nodeToPrint->getValue() << endl;
        nodeToPrint = nodeToPrint->getNext();
    }
    cout << "End Of List Contents" << endl;
}
  
template <class T>
void SortedListClass<T>::printBackward() const {
    cout << "Backward List Contents Follow:" << endl;
    LinkedNodeClass<T> *nodeToPrint = tail;
    while (nodeToPrint != 0) {
        cout << "  " << nodeToPrint->getValue() << endl;
        nodeToPrint = nodeToPrint->getPrev();
    }
    cout << "End Of List Contents" << endl;
}
  
template <class T>
bool SortedListClass<T>::removeFront( 
    T &theVal 
) {
    //return false if list is empty
    if (head == 0) {
        return false;
    }
    //if the list contains one node
    if (getNumElems() == 1) {
        theVal = head->getValue();
        clear();
        return true;
    }
    //otherwise
    //extract value
    theVal = head->getValue();
    //move to new head
    head = head->getNext();
    //delete the old head
    delete head->getPrev();
    //set up the new head appropriately
    head->setPreviousPointerToNull();
    return true;
}
  
template <class T>
bool SortedListClass<T>::removeLast( 
    T &theVal 
) {
    //return false if list is empty
    if (head == 0) {
        return false;
    }
    //if the list contains one node
    if (getNumElems() == 1) {
        theVal = tail->getValue();
        clear();
        return true;
    }
    //otherwise
    //extract value
    theVal = tail->getValue();
    //move to new tail
    tail = tail->getPrev();
    //delete the old tail
    delete tail->getNext();
    //set up the new tail appropriately
    tail->setNextPointerToNull();
    return true;
}
  
template <class T>
int SortedListClass<T>::getNumElems() const {
    LinkedNodeClass<T> *tempNode = head;
    int count = 0;
    while (tempNode != 0) {
        tempNode = tempNode->getNext();
        count++;
    }
    return count;
}
  
template <class T>
bool SortedListClass<T>::getElemAtIndex( 
    const int index, 
    T &outVal 
) const {
    //return false if index out of range
    if (index < 0 || index >= getNumElems()) {
        return false;
    }
    //otherwise return true and get value
    LinkedNodeClass<T> *tempNode = head;
    int location = 0;
    while (tempNode != 0) {
        if (location == index) {
            outVal = tempNode->getValue();
            return true;
        }
        tempNode = tempNode->getNext();
        location++;
    }
    return true;
}