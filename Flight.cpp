#include "Flight.h"

Flight::Flight(const string &flightID, const string &origin, const string &destination, const string &departureDate, const string &departureTime, int capacity): flightID(flightID), origin(origin), destination(destination),departureDate(departureDate), departureTime(departureTime), capacity(capacity) {}

string Flight::getFlightID() const { return flightID; }
string Flight::getOrigin() const { return origin; }
string Flight::getDestination() const { return destination; }
string Flight::getDepartureDate() const { return departureDate; }
string Flight::getDepartureTime() const { return departureTime; }
int Flight::getCapacity() const { return capacity; }

void Flight::print() const {
    cout << "Flight Number: " << flightID
    << ", Origin: " << origin
    << ", Destination: " << destination
    << ", Date: " << departureDate
    << ", Time: " << departureTime
    << ", Capacity: " << capacity;
}
