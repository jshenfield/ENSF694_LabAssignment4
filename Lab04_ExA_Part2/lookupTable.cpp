#include "lookupTable.h"
#include "Point.h"
#include <iostream>


/*
 *  lookupTable.cpp
 *  ENSF 694 Lab 4, exercise A
 *  Created by Mahmood Moussavi
 *  Completed by: Jack Shenfield
 *  Development Date: July 29th, 2025
 */

// constructor for LT_Node struct
LT_Node::LT_Node(const Pair& pairA, LT_Node *nextA):pairM(pairA), nextM(nextA){}

// initialize all member variables to 0
LookupTable::LookupTable(){
    sizeM = 0; 
    headM = nullptr;
    cursorM = nullptr;
}

// copy ctor
LookupTable::LookupTable(const LookupTable  & source):sizeM(source.sizeM), headM(nullptr), cursorM(nullptr){
    if(source.headM == nullptr){
        return; // list to be copied is empty
    }

    // copy head node into headM
    headM = new LT_Node(source.headM->pairM, nullptr);
    LT_Node * src = source.headM->nextM; // track old list in iteration
    LT_Node * dest = headM; // track new list

    // point cursor to head
    cursorM = headM;

    while(src != nullptr){
        dest->nextM = new LT_Node(src->pairM, nullptr); // create new node using src data
        dest = dest->nextM; // update pointer to new node
        if(src == source.cursorM){
            cursorM = dest;
        }
        src = src->nextM;
    }
}



// assignment operator
LookupTable& LookupTable::operator =(const LookupTable& rhs){
    // if it is the same object return it
    if (this == &rhs){
        return *this;
    } 

    // reset to initial values
    sizeM = rhs.sizeM;
    headM = nullptr;
    cursorM = nullptr;

    // If it is empty, return it
    if (rhs.headM == nullptr){
        return *this;
    }

    // Create new node
    headM = new LT_Node(rhs.headM->pairM, nullptr);

    LT_Node* src = rhs.headM->nextM;
    LT_Node* dest = headM;

    cursorM = headM;


    // Loop through and create new list
    while (src != nullptr) {
        dest->nextM = new LT_Node(src->pairM, nullptr);
        dest = dest->nextM;
        if (src == rhs.cursorM) {
            cursorM = dest;
        }
        src = src->nextM;
    }

    return *this;
}

// dtor
LookupTable::~LookupTable(){
    make_empty(); // call the make empty function created later on.
}
LookupTable& LookupTable::begin(){
    cursorM = headM;
    return *this;
}

int LookupTable::size() const{
    return sizeM;
}

int LookupTable::cursor_ok() const{
    if(cursorM == nullptr){ // pointing at nothing, return 0
        return 0;
    }
    else{ // if not pointing at nothing, assume pointing at list
        return 1;
    }
}

const int& LookupTable::cursor_key() const{
    if(cursor_ok() == 1){
        return cursorM->pairM.key;
    }
}

const Type& LookupTable::cursor_datum() const{
    if(cursor_ok() == 1){
        return cursorM->pairM.datum;
    }
}

// inserts keys in order
void LookupTable::insert(const Pair& pairA) {
    cursorM = headM;
    LT_Node* prev = nullptr;

    // Check if key already exists — if so, update the datum
    while (cursorM != nullptr) {
        if (cursorM->pairM.key == pairA.key) {
            cursorM->pairM.datum = pairA.datum;
            cursorM = nullptr;
            return;
        }
        if (cursorM->pairM.key > pairA.key) {
            break;  // found insert position
        }
        prev = cursorM;
        cursorM = cursorM->nextM;
    }

    // Create new node to insert
    LT_Node* newNode = new LT_Node(pairA, cursorM);

    if (prev == nullptr) {
        // Insert at head
        headM = newNode;
    } else {
        prev->nextM = newNode;
    }

    cursorM = nullptr;
    ++sizeM;
}




int LookupTable::remove(const int& keyA){

    cursorM = nullptr; // off-list

    LT_Node* prev = nullptr;
    cursorM = headM;

    while (cursorM != nullptr) {
        if (cursorM->pairM.key == keyA) {
            // Remove node
            if (prev == nullptr) {
                // Node head
                headM = cursorM->nextM;
            } else {
                // Node is not at head
                prev->nextM = cursorM->nextM;
            }
            
            int removed = cursorM->pairM.key;
            delete cursorM;
            cursorM = nullptr;
            --sizeM;
            return removed; // return the removed key
        }

        prev = cursorM;
        cursorM = cursorM->nextM;
    }

    cursorM = nullptr;

    return 0; // key not found
}

void LookupTable::find(const int& keyA){
 
    cursorM = headM;

    // search for key
    while(cursorM != nullptr){
        if(cursorM->pairM.key == keyA){
            return;
        }
        cursorM = cursorM->nextM;
    }

    cursorM = nullptr;
}

void LookupTable::go_to_first(){
    if(sizeM > 0){
        cursorM = headM;
    }
    else{
        cursorM = nullptr;
    }
}

void LookupTable::step_fwd(){
    if(cursorM->nextM == nullptr || cursor_ok() == 0){
        cursorM = nullptr;
    }
    else{
        cursorM = cursorM->nextM;
    }
}

void LookupTable::make_empty(){

    // delete each node from memory going down the list
    LT_Node* current = headM;
    while (current != nullptr) {
        LT_Node* temp = current;
        current = current->nextM;
        delete temp;
    }

    // reset variables
    headM = nullptr;
    cursorM = nullptr;
    sizeM = 0;
}


void LookupTable::display()const{
    LT_Node* ptr = headM;

    // print lines
    while (ptr != nullptr) {
        std::cout << "[" << ptr->pairM.key << ": " << ptr->pairM.datum << "] ";
        ptr = ptr->nextM;
    }
    std::cout << std::endl; // endline
}


bool LookupTable::isEmpty()const{
    if(sizeM == 0){
        return true;
    }
    else{
        return false;
    }
}

int LookupTable::retrieve_at(int i){
    if(i < 0 || i >= sizeM){
        throw std::out_of_range("Index DNE"); // index doesn't exist
    }

    cursorM = headM;
    int index = 0;

    while(cursorM != nullptr && index < i){
        cursorM = cursorM->nextM;
        index++;
    }
    
    if(cursorM != nullptr){
        return cursorM->pairM.key;
    }

}


