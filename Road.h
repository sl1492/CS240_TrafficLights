#ifndef __ROAD_H__
#define __ROAD_H__

#include "MSection.h"
#include "Section.h"
#include "Light.h"
#include "VehicleBase.h"
#include <vector>
using namespace std;

class Road{
private:
    vector<Section *> road;    
    int length;            
    Direction dir;        
    Section* buffer;           
    TrafficLight* trafficLight;
    Section* linkSections(int numOfSections, Section* lastSection);

public:
    Road(){};
    Road(Direction dir, int halfSize, MSection* mSection1, MSection* mSection2, TrafficLight* light);
    ~Road();

    vector<VehicleBase*> getRoad();                         
    inline Section* getBuffer(){ return buffer; }                  
    inline Direction getDirection(){ return dir; }          
    inline TrafficLight* getTrafficLight(){ return trafficLight; } 
    bool PossibleVeh();                                            
};

#endif
