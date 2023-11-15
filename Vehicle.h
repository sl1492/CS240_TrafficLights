#ifndef __VEHICLE_H__
#define __VEHICLE_H__
#include "MSection.h"
#include "VehicleBase.h"
#include "Road.h"
#include "Section.h"

class Vehicle : public VehicleBase{
private:

    Road *road;            
    Section *start;       
    Section *end;       
    int length;             
    bool atTheEnd = false; 
    bool turningRight;    
    void moveForward();
    void turnRight();

public:

    Vehicle(Road *spawnRoad, VehicleType type, bool willTurn);
    ~Vehicle(){}
    void move();                                  
    inline bool reachedEnd(){ return atTheEnd; }   
    inline bool willTurn(){ return turningRight; } 
};
#endif
