/*
 *  lab4exe_E.cpp
 *  ENSF 694 Lab 4, exercise E
 *  Created by Mahmood Moussavi
 *  Completed by: Jack Shenfield
 *  Development Date: July 30th, 2025
 */


#include "HashTable.h"

// function definitions
 

int HashTable::hashFunction(const std::string &flightID) const{ // inspired by chatGPT
    unsigned int hash = 0;

    for (char c : flightID) {
        hash = hash * 31 + c;  // prime number multiplier is 31
    }
    return hash % tableSize; //
}

// constructor, initialize most values at 0. size at inputted size.
HashTable::HashTable(int size):tableSize(size), totalRecords(0), nonCollisionCount(0), elementsUsed(0) {

    table = new List*[tableSize];
    for (int i = 0; i < tableSize; ++i)
        table[i] = nullptr; // fill table with null pointers
}

HashTable::~HashTable(){
    for (int i = 0; i < tableSize; ++i) { // delete each value

        if (table[i] != nullptr)
            delete table[i];
    }

    delete[] table; // delete the leftover empty table

}

void HashTable::insert(const Flight &flight){

    int ind = hashFunction(flight.getFlightID()); // compute hash # (useable index) with my prime function

    if (table[ind] == nullptr) { // If there is no value at this index

        table[ind] = new List(); // create a new List at the computed hash #
        table[ind]->insert(flight); // insert the flight into that list

        nonCollisionCount++; // There was no collision here. increment
        elementsUsed++; // new element

    } else {
        table[ind]->insert(flight); // there is already a flight here, chain to previous one.
    }

    totalRecords++; // increment total records

}

Flight* HashTable::search(const std::string &flightID)const{

    int index = hashFunction(flightID); // compute hash # from inputted flight ID

    if (table[index] == nullptr){
        return nullptr; // If there is nothing at the index, return nullptr
    }
    Node* result = table[index]->search(flightID);
    return result ? &result->data : nullptr; // return the result or nullptr depending on result
}

void HashTable::printTable() const{

    for (int i = 0; i < tableSize; ++i) {
        std::cout << "Chain " << i << ": ";
        if (table[i]) // print if there is values
            table[i]->printList();
        else // else, print empty
            std::cout << "Empty";
        std::cout << std::endl;
    }
}

double HashTable::getNonCollisionEfficiency() const{

    if (totalRecords == 0){
        return 0.0; // no values, return nothing.
    }
    // otherwise, return non collision %
    return ((double)nonCollisionCount / totalRecords * 100.0);
}


int HashTable::calculateTotalSearchCost()const{
    int totalCost = 0; // initialize at 0;

    for (int i = 0; i < tableSize; ++i) {
        List* chain = table[i]; //
        if (chain != nullptr) {

            Node* current = chain->getHead(); // point at head index of chain

            int position = 1;

            while (current != nullptr) { // for each real value
                totalCost += position;  // search cost is the position
                current = current->next; // move to next value
                ++position; // increment

            }
        }

    }


    return totalCost;
}

double HashTable::getTableDensity() const{
    return(static_cast<double>(elementsUsed) / tableSize); // number of elements used / total table size
}

double HashTable::getPackingDensity() const{
    return(static_cast<double>(totalRecords) / tableSize); // number of total records / table size
}

double HashTable::getHashEfficiency() const{

    if (totalRecords == 0) return 0.0; // if empty, return 0.0

    return(static_cast<double>(calculateTotalSearchCost()) / totalRecords); // otherwise, return search cost / total table size
}