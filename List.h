#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include <string>

class List {
private:
    Node* head;
public:
    List();
    ~List();
    void insert(const Flight &flight);
    // Search for a flight by flightID; returns pointer to Node if found, otherwise nullptr.
    Node* search(const std::string &flightID) const;
    void printList() const;
    int getSize() const; // Number of nodes in the list
    bool isEmpty() const;
};

#endif
