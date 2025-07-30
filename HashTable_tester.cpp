
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "HashTable.h"
#include "Flight.h"
#include <string>
using namespace std;

void read_flight_info(ifstream &fin, vector<Flight> &flights) {
    string line;
    while (getline(fin, line)) {
        if (line.empty())
            continue;
        istringstream iss(line);
        string flightID, origin, destination, depDate, depTime;
        int capacity;
        // You can adjust the reading logic if fields are fixed width.
        if (!(iss >> flightID >> origin >> destination >> depDate >> depTime >> capacity)) {
            cerr << "Malformed record: " << line << endl;
            continue;
        }
        Flight flight(flightID, origin, destination, depDate, depTime, capacity);
        flights.push_back(flight);
    }
}

void interactive_search(const HashTable& hashTable) {
    string input;
    cout << "\n\nInteractive Search ... \n";
    while (true) {
        cout << "\nEnter flight number to search (or 'exit' to quit): ";
        cin >> input;
        if (input == "exit")
            break;
        Flight* found = hashTable.search(input);
        if (found) {
            cout << "Record found: ";
            found->print();
            cout << endl;
        } else {
            cout << "No record found for flight number \"" << input << "\"." << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    // Check command line arguments.
    if (argc != 2) {
        cout << "usage: hashtable input_file" << endl;
        return 1;
    }
    
    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Error: cannot open file " << argv[1] << endl;
        return 1;
    }

    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Error: cannot open file " << argv[1] << endl;
        return 1;
    }
    // Read flight records from the input file.
    vector<Flight> flights;
    read_flight_info(fin, flights);
    fin.close();
    
    if (flights.empty()) {
        cerr << "No flight records found in the file." << endl;
        return 1;
    }
    
    // Decide on table size.
    // For a packing density similar to sample output (e.g., 2 records per bucket),
    // we choose tableSize = number of records / 2 (with a minimum of 1).
    int tableSize = (int) flights.size();
    if (tableSize < 1)
        tableSize = 1;
    
    HashTable hashTable(tableSize);
    
    // Insert all flights into the hash table.
    for (const Flight &flight : flights) {
        hashTable.insert(flight);
    }
    
    // Print statistics.
    cout << "Number of Records: " << hashTable.getTotalRecords()<< endl;
    cout << "Table Size: " << hashTable.getTableSize()<< endl;
    cout << "Table Density: " << hashTable.getTableDensity() *100 << "%"<< endl;
    cout << "Non-collision Efficiency: " << hashTable.getNonCollisionEfficiency()*100 << "%"<<endl;
    cout << "Packing Density: " << hashTable.getPackingDensity() << endl;
    cout << "Hash Efficiency: " << fixed << setprecision(1) << hashTable.getHashEfficiency() *100 << "%"<<endl;
    hashTable.printTable();
    interactive_search(hashTable);
    
    return 0;
}
