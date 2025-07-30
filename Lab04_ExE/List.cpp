#include "List.h"
#include <iostream>

List::List() : head(nullptr) {}

List::~List() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void List::insert(const Flight &flight) {
    // Insert at the head of the list
    Node* newNode = new Node(flight);
    newNode->next = head;
    head = newNode;
}

Node* List::search(const std::string &flightID) const {
    Node* current = head;
    while (current) {
        if (current->data.getFlightID() == flightID)
            return current;
        current = current->next;
    }
    return nullptr;
}

void List::printList() const {
    Node* current = head;
    while (current) {
        current->data.print();
        std::cout << std::endl;
        current = current->next;
    }
}

int List::getSize() const {
    int count = 0;
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

bool List::isEmpty() const {
    return head == nullptr;
}
