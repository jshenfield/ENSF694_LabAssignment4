
#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H
#include <iostream>
using namespace std;

// class LookupTable: GENERAL CONCEPTS
//
//    key/datum pairs are ordered.  The first pair is the pair with
//    the lowest key, the second pair is the pair with the second
//    lowest key, and so on.  This implies that you must be able to
//    compare two keys with the < operator.
//
//    Each LookupTable has an embedded iterator class that allows users
//    of the class to traverse trhough the list and  have acess to each
//    node.
//    In this version of the LookupTable a new struct type called Pair
//    is introduced which represents a key/data pair.

typedef string Type;

struct Pair
{   // This ctor is writtent for convenience in creating objects of Pair and copy
    Pair(int keyA,Type datumA):key(keyA), datum(datumA)
    {
    }
    
    int key;
    Type datum;
};

struct LT_Node {
    Pair pairM;
    LT_Node *nextM;
    // This ctor should be convenient in insert and copy operations.
    LT_Node(const Pair& pairA, LT_Node *nextA);
    // PROMISES: initializes the data members pairM and nextM, with pairA and nextA
    // respectively
};

class LookupTable {
public:
    // Nested class
    LookupTable();
    // PROMISES: An empty LookupTable object with all data members. Setting size, cursor and
    // head to zero or nullptr
    // copy ctor
    LookupTable(const LookupTable  & source);
    
    // assignment operator
    LookupTable& operator =(const LookupTable& rhs);
    
    // dtor
    ~LookupTable();
    
    LookupTable& begin();
    // PROMISES: Moves cursorM to the beginning of the list
    
    int size() const;
    // PROMISES: Returns number of keys in the table.
    
    int cursor_ok() const;
    // PROMISES:
    //   Returns 1 if the cursor is attached to a key/datum pair,
    //   and 0 if the cursor is in the off-list state.
    
    const int& cursor_key() const;
    // REQUIRES: cursor_ok()
    // PROMISES: Returns key of key/datum pair to which cursor is attached.
    
    const Type& cursor_datum() const;
    // REQUIRES: cursor_ok()
    // PROMISES: Returns datum of key/datum pair to which cursor is attached.
    
    void insert(const Pair& pariA);
    // PROMISES:
    //   If keyA matches a key in the table, the datum for that
    //   key is set equal to datumA.
    //   If keyA does not match an existing key, keyA and datumM are
    //   used to create a new key/datum pair in the table.
    //   In either case, the cursor goes to the off-list state.
    
    int remove(const int& keyA);
    // PROMISES:
    //   If keyA matches a key in the table, the corresponding
    //   key/datum pair is removed from the table.
    //   If keyA does not match an existing key, the table is unchanged.
    //   In either case, the cursor goes to the off-list state.
    
    void find(const int& keyA);
    // PROMISES:
    //   If keyA matches a key in the table, the cursor is attached
    //   to the corresponding key/datum pair.
    //   If keyA does not match an existing key, the cursor is put in
    //   the off-list state.
    
    void go_to_first();
    // PROMISES: If size() > 0, cursor is moved to the first key/datum pair
    //   in the table.
    
    void step_fwd();
    // REQUIRES: cursor_ok()
    // PROMISES:
    //   If cursor is at the last key/datum pair in the list, cursor
    //   goes to the off-list state.
    //   Otherwise the cursor moves forward from one pair to the next.
    
    void make_empty();
    // PROMISES: size() == 0.
    
    void display()const;
    // PROMISES: displays the values o
    bool isEmpty()const;
    // PROMISES: returns true is list is empty
    
    int* retrieve_at(int i);
    // PROMISES: returns the adress of the key at the position index. Reminder: the index
    // number for the first node in the list is 0, 2nd node is 1, 3rd node is 2 and so on.
    
private:
    int sizeM;        // size of list (number of availble nodes)
    LT_Node *headM;   // pointer to the first node in the list
    LT_Node *cursorM; // pointer that can travers through the list
    void destroy();
    // Deallocate all nodes, set headM to zero.
    void copy(const LookupTable& source);
    // Establishes *this as a copy of source.  Cursor of *this will
    // point to the twin of whatever the source's cursor points to.
};

#endif




