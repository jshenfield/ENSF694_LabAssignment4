#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <iostream>
using namespace std;
class Flight {
private:
    string flightID;
    string origin;
    string destination;
    string departureDate;
    string departureTime;
    int capacity;
public:
    Flight() = default;
    Flight(const string &flightID, const string &origin, const string &destination,
           const string &departureDate, const string &departureTime, int capacity);
    
    // Getters
    string getFlightID() const;
    string getOrigin() const;
    string getDestination() const;
    string getDepartureDate() const;
    string getDepartureTime() const;
    int getCapacity() const;
    
    // Print the flight information
    void print() const;
};

#endif
