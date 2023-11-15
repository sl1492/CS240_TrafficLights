#ifndef __MSECTION_CPP__
#define __MSECTION_CPP__
#include "MSection.h"
#include "Vehicle.h"
using namespace std;

// Default constructor
MSection::MSection():Section(){ 
    middle = true; 
}

// Destructor
MSection::~MSection(){} 

// If turning right, get the next section
Section *MSection::getRight(){
    Direction dir = getVehicle()->getVehicleOriginalDirection();
    if(dir == Direction::north) {
        return east;
    }
    else if(dir == Direction::east) {
        return south;
    }
    else if(dir == Direction::west) {
        return north;
    }
    else if(dir == Direction::south) {
        return west;
    }
    return nullptr;
}

// Get the previous section according to the direction vehicle is travelling
Section *MSection::getLast(){
    if(getVehicle() == nullptr)
        return Section::getLast();

    // Convert the pointer to VehicleBase into the pointer to Vehicle
    Vehicle *veh = dynamic_cast<Vehicle *>(getVehicle());
    Direction dir = veh->getVehicleOriginalDirection();

        // If a vehicle is turning return sections from previous direction
    if(veh->willTurn()){
        if(dir == Direction::north) {
            return east;
        }
        else if(dir == Direction::east) {
            return south;
        }
        else if(dir == Direction::west) {
            return north;
        }
        else if(dir == Direction::south) {
            return west;
        }
    }
    else {
        if(dir == Direction::north) {
          return south;
        }
        else if(dir == Direction::east) {
            return west;
        }
        else if(dir == Direction::west) {
            return east;
        }
        else if(dir == Direction::south) {
            return north;
        }
    }
    return nullptr;
}

// Get the next section according to the direction vehicle is travelling
Section *MSection::getNext(){
    Direction dir = getVehicle()->getVehicleOriginalDirection();
    if(dir == Direction::north) {
        return north;
    }
    else if(dir == Direction::east) {
        return east;
    }
    else if(dir == Direction::west) {
        return west;
    }
    else if(dir == Direction::south) {
        return south;
    }
    else {
        Section::getNext();
    }
    return nullptr;
}


#endif
