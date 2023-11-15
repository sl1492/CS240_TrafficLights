#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <string>
#include "VehicleBase.h"

class TrafficLight {
public:
    TrafficLight();
    TrafficLight(int green, int yellow, int red, LightColor color);
    ~TrafficLight(){} 

    LightColor getColor() const;
    int getTimeLeft() const;
    void decrementTimeLeft();

private:
    int m_green;         
    int m_yellow;      
    int m_red;            
    int m_timeLeft;
    LightColor m_color;
};

#endif
