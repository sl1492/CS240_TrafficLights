#ifndef __Section_CPP__
#define __Section_CPP__
#include "Section.h"
using namespace std;

// Default Constructor
Section::Section(){
    empty = true;
    setNext(nullptr);
    setLast(nullptr);
}


// Destructor
Section::~Section(){
    if (vehicle != nullptr) {
    delete vehicle;
    }
}   


// Copy Constructor
Section::Section(const Section& other) {
    next = other.next;
    last = other.last;
    empty = other.empty;
    middle = other.middle;

    if (other.vehicle!= nullptr) {
        vehicle = new VehicleBase(*other.vehicle);
    } else {
        vehicle = nullptr;
    }
}


// Copy Assignment Operator
Section& Section::operator=(const Section& other) {
    if (this == &other) {
        return *this;
    }
    next = other.next;
    last = other.last;
    empty = other.empty;
    middle = other.middle;

    if (vehicle != nullptr) {
        delete vehicle;
    }
    if (other.vehicle != nullptr) {
        vehicle = new VehicleBase(*other.vehicle);
    } else {
        vehicle = nullptr;
    }
    return *this;
}


// Move Constructor
Section::Section(Section&& other) noexcept
    : next(other.next), last(other.last),
      empty(other.empty), vehicle(other.vehicle), middle(other.middle) {
    // move member variables
    other.next = nullptr;
    other.last = nullptr;
    other.vehicle = nullptr;
    other.empty = true;
    other.middle = false;
}


// Move Assignment Operator
Section& Section::operator=(Section&& other) noexcept{
    if (this != &other) {
        if (vehicle != nullptr) {
            delete vehicle;
        }
        next = other.next;
        last = other.last;
        empty = other.empty;
        middle = other.middle;
        vehicle = other.vehicle;

        other.next = nullptr;
        other.last = nullptr;
        other.empty = true;
        other.middle = false;
        other.vehicle = nullptr;
    }
    return *this;
}

// Put a vehicle on this Section;
void Section::putVehicle(VehicleBase *vehicle){
    empty = false;
    this->vehicle = vehicle;
}

// Remove a vehicle;
void Section::Remove(){
    empty = true;
    this->vehicle = nullptr;
}


#endif
