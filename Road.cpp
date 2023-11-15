#ifndef __ROAD_CPP__
#define __ROAD_CPP__
#include "Road.h"

// Link two sections together, set last and next
Section* Road::linkSections(int numOfSections, Section* lastSection){
    for (int i = 0; i < numOfSections; i++){
        Section* section = new Section();
        section->setLast(lastSection);
        lastSection->setNext(section);
        lastSection = section;
        road.push_back(section);
    }
    return lastSection;
}

// Constructor for creating a road
Road::Road(Direction dir, int halfSize, MSection* mSection1, MSection* mSection2, TrafficLight* light){
    trafficLight = light;
    length = 2 + halfSize * 2;   
    this->dir = dir;

    // Create a buffer by linking sections
    Section *lastSection = nullptr;
    for (int i = 0; i < 4; i++){
        Section *section = new Section();
        if (i == 3)
            buffer = section;
        if (lastSection != nullptr){
            section->setLast(lastSection);
            lastSection->setNext(section);
        }
        lastSection = section;
        road.push_back(section);
    }

    // Link first half of sections before the intersections
    lastSection = linkSections(halfSize, lastSection);

    // Add the middle sections
    road.push_back(mSection1);

    // Link first middle section
    lastSection->setNext(mSection1);
    mSection1->setLast(lastSection);

    // Create a section right after the intersection
    Section *startOfSecondHalf = new Section();

    // Link North East West South for middle sections based on the direction
    if(dir == Direction::north){
        mSection1->setSouth(lastSection);
        mSection1->setNorth(mSection2);
        mSection2->setSouth(mSection1);
        mSection2->setNorth(startOfSecondHalf);
    } else if(dir == Direction::east){
        mSection1->setWest(lastSection);
        mSection1->setEast(mSection2);
        mSection2->setWest(mSection1);
        mSection2->setEast(startOfSecondHalf);
    } else if(dir == Direction::west){
        mSection1->setEast(lastSection);
        mSection1->setWest(mSection2);
        mSection2->setEast(mSection1);
        mSection2->setWest(startOfSecondHalf);
    } else if(dir == Direction::south){
        mSection1->setNorth(lastSection);
        mSection1->setSouth(mSection2);
        mSection2->setNorth(mSection1);
        mSection2->setSouth(startOfSecondHalf);
    }

    // Link middlesection2 and startofSecondHalf
    road.push_back(mSection2);
    road.push_back(startOfSecondHalf);
    startOfSecondHalf->setLast(mSection2);
    lastSection = startOfSecondHalf;

    // Link the second half and the end buffer
    linkSections(halfSize + 4, lastSection);
}

// Destructor deallocates every section except middle ones
Road::~Road(){
    for (size_t i = 0; i < road.size(); i++){
        if (!road[i]->isMiddle())
            delete this->road[i];
    }
    road.clear();
}

// Get a verctor of a road;
vector<VehicleBase*> Road::getRoad(){
    vector<VehicleBase *> roadVector(length, nullptr);
    for (int i = 0; i < length; i++){
        if (!road[i + 4]->isEmpty())
            roadVector[i] = road[i + 4]->getVehicle();
    }
    return roadVector;
}

// For checking if there is space for creating vehicles
bool Road::PossibleVeh(){
    for (size_t i = 0; i < 4; i++){
        if (!road[i]->isEmpty())
            return false;
    }
    return true;
}

#endif

