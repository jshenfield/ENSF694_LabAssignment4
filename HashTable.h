#if 0 // OLD solution using differnet calcuation of hashing efficiency
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "List.h"
#include "Flight.h"
#include <string>

class HashTable {
private:
    List** table;      // Array of pointers to List objects (buckets)
    int tableSize;
    int totalRecords;
    int nonCollisionCount;
    
    // Simple hash function: polynomial accumulation using multiplier 31.
    int hashFunction(const std::string &flightID) const;
public:
    HashTable(int size);
    ~HashTable();
    void insert(const Flight &flight);
    Flight* search(const std::string &flightID);
    void printTable() const;
    double getPackingDensity() const;  // records per bucket (totalRecords/tableSize)
    double getHashEfficiency() const;  // percentage of non-collision insertions
};

#endif
#endif



// new solution
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "List.h"
#include "Flight.h"
#include <string>

class HashTable {
private:
    List** table;      // Array of pointers to List objects (buckets)
    int tableSize;
    int totalRecords;
    int nonCollisionCount; // counter to track number of non-collison records
    int elementsUsed;      // the number of elements of the table that are use
    
    // Simple hash function
    int hashFunction(const std::string &flightID) const;
public:
    HashTable(int size);
    ~HashTable();
    void insert(const Flight &flight);
    Flight* search(const std::string &flightID)const;
    void printTable() const;
    int getTableSize()const {return tableSize;};
    int getTotalRecords()const {return totalRecords;};
    double getNonCollisionEfficiency() const;
    int calculateTotalSearchCost()const;
    double getTableDensity() const;
    double getPackingDensity() const;
    double getHashEfficiency() const;
};

#endif
