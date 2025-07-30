#include "Point.h"
#include <cstring>
#include <iostream>

/*
 *  Point.cpp
 *  ENSF 694 Lab 4, exercise A Part II
 *  Created by Mahmood Moussavi
 *  Completed by: Jack Shenfield
 *  Development Date: July 29th, 2025
 */



Point::Point(int x, int y, const char* label):x(x),y(y){

    if (label) {
        this->label = new char[strlen(label) + 1];
        std::strcpy(this->label, label);
    } else {
        this->label = nullptr;
    }
}


Point::~Point(){
    delete [] label;
}

// cpy
Point::Point(const Point& src):x(src.x), y(src.y){

    if (src.label) {
        label = new char[strlen(src.label) + 1];
        std::strcpy(label, src.label);
    } else {
        label = nullptr;
    }


}

// operator
Point& Point::operator=(const Point& rhs) {
    if (this == &rhs){
        return *this; // self-assignment
    }

    // delete label
    delete[] label;

    // copy values
    x = rhs.x;
    y = rhs.y;
    if (rhs.label) {
        label = new char[strlen(rhs.label) + 1]; // allocate memory
        std::strcpy(label, rhs.label);
    } else {
        label = nullptr; // label DNE
    }

    return *this;
}

// getter
int Point::getx() const{
    return x;
}

// getter
int Point::gety() const{
    return y;
}

// getter
char* Point::get_label()const{
    return label;
}
    

// overloading << operator to be able to print points 
// some help here from chatGPT
std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.getx() << ", " << p.gety() << ", " << p.get_label() << ")";
    return os;
}