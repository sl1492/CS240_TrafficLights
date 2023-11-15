#ifndef __Light_CPP__
#define __Light_CPP__

#include <string>
#include "Light.h"
using namespace std;

// Default Constructor;
TrafficLight::TrafficLight()
    : m_green(0), m_yellow(0), m_red(0), m_timeLeft(0), m_color(LightColor::red) {}

// Constructor for setting up time;
TrafficLight::TrafficLight(int green, int yellow, int red, LightColor color)
    : m_green(green), m_yellow(yellow), m_red(red), m_color(color) {
    if (m_color == LightColor::green)
        m_timeLeft = m_green;
    else if (m_color == LightColor::yellow)
        m_timeLeft = m_yellow;
    else
        m_timeLeft = m_red;
}

// Get the color of the traffic light
LightColor TrafficLight::getColor() const {
    return m_color;
}

// Get the time left for a traffic light
int TrafficLight::getTimeLeft() const {
    return m_timeLeft;
}

// Decrement the time left for each traffic light and change traffic light color
void TrafficLight::decrementTimeLeft() {
    --m_timeLeft;
    if (m_timeLeft == 0) {
        if (m_color == LightColor::green) {
            m_color = LightColor::yellow;
            m_timeLeft = m_yellow;
        }
        else if (m_color == LightColor::yellow) {
            m_color = LightColor::red;
            m_timeLeft = m_red;
        }
        else {
            m_color = LightColor::green;
            m_timeLeft = m_green;
        }
    }
}

#endif