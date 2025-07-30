#ifndef NODE_H
#define NODE_H

#include "Flight.h"

struct Node {
    Flight data;
    Node* next;
    Node(const Flight &flight) : data(flight), next(nullptr) {}
};

#endif
