#ifndef __VEHICLE_CPP__
#define __VEHICLE_CPP__

#include "MSection.h"
#include "Vehicle.h"
#include <iostream>

// Constructor
Vehicle::Vehicle(Road *spawnRoad, VehicleType type, bool willTurn) : VehicleBase(type, spawnRoad->getDirection()){
    road = spawnRoad;
    turningRight = willTurn;
    if(type == VehicleType::car)
        length = 2;
    else if(type == VehicleType::suv)
        length = 3;
    else
        length = 4;

    start = road->getBuffer();
    start->putVehicle(this);
    end = start;

    // Move tail on length distance
    for(int i = 0; i < length - 1; i++){
        end = end->getLast();
        end->putVehicle(this);
    }
}

// Move vehicle exactly one section forward or to the right
void Vehicle::move(){
    // If the next section is not empty or null
    if(!(start->getNext()->isEmpty()) || (start->getNext() == nullptr))
        return;
    // If a vehicle is on the intersection
    else if(start->getNext()->isMiddle() && !(start->isMiddle())){
        LightColor trafficColor = road->getTrafficLight()->getColor();
        // Stop if the color is red
        if(trafficColor == LightColor::red){
            return;
        }
        // Stop if the color is yellow and a vehicle has no time to proceed
        else if(trafficColor == LightColor::yellow){
            int timeTilChange = road->getTrafficLight()->getTimeLeft();
            // It takes less time to turn right than go straight
            if(turningRight && (timeTilChange < length + 1))
                return;
            if(!turningRight && (timeTilChange < length + 2))
                return;
        }
    }
    // Turn right if the head is already at the intersection
    else if(start->getNext()->isMiddle() && start->isMiddle() && turningRight){
        turnRight();
        return;
    }
    moveForward();

    // If next section is null, vehicle has reached the end
    if(start->getNext() == nullptr){
        atTheEnd = true;
        Section *sec = start;
        // Empty the sections where was a vehicle
        while(sec != end){
            sec->Remove();
            sec = sec->getLast();
        }
        end->Remove();
    }
}

// Helper method used for move()
void Vehicle::moveForward(){
    start = start->getNext();
    start->putVehicle(this);
    end = end->getNext();
    end->getLast()->Remove();
}

// Helper method for move()
void Vehicle::turnRight(){
    MSection *ms = dynamic_cast<MSection *>(start);
    start = ms->getRight();
    start->putVehicle(this);
    end->Remove();
    end = end->getNext();
    if(getVehicleOriginalDirection() == Direction::east)
        changeDirection(Direction::south);
    else if(getVehicleOriginalDirection() == Direction::north)
        changeDirection(Direction::east);
    else if(getVehicleOriginalDirection() == Direction::west)
        changeDirection(Direction::north);
    else if(getVehicleOriginalDirection() == Direction::south)
        changeDirection(Direction::west);
}

#endif