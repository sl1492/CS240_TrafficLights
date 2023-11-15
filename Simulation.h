#ifndef __SIMULATION_H__
#define __SIMULATION_H__
#include "Animator.h"
#include "Section.h"
#include "MSection.h"
#include "Road.h"
#include "Light.h"
#include "Vehicle.h"
#include <string>
#include <vector>
using namespace std;

class Simulation{
private:
    vector<Vehicle *> vehicleVector;   // Vector of all vehicles in system
    int seed;                          
    int maxTime;                       // Maximum simulation time
    int sectionsBeforeIntersection;    // Number of tiles before intersection for each road
    int nsGreen;                       // Amount of time that the north-south light is green
    int nsYellow;                      // Amount of time that the north-south light is yellow
    int ewGreen;                       // Amount of time that the east-west light is green
    int ewYellow;                      // Amount of time that the east-west light is yellow
    double pNewVehicleN;            // Probability a new vehicle is generated northbound
    double pNewVehicleS;            // Probability a new vehicle is generated southbound
    double pNewVehicleE;            // Probability a new vehicle is generated eastbound
    double pNewVehicleW;            // Probability a new vehicle is generated westbound
    double Pcars;             // Proportion of generated vehicles that are cars
    double Psuvs;             // Proportion of generated vehicles that are SUV
    double Ptrucks;           // Proportion of generated vehicles that are trucks
    double pRCars;              // Probability a car turns right
    double pRSUVs;              // Probability a SUV turns right
    double pRTrucks;            // Probability a truck turns right
    double pLCars;               // Probability a car turns left
    double pLSUVs;               // Probability a SUV turns left
    double pLTrucks;             // Probability a truck turns left

    void createVehicle(Road *road, double roadProb, double createProb, double vehicleProb, double turnProb);  
    void step();  

public:
    Simulation(){}
    Simulation(string file, int seed);
    ~Simulation();
    void SetupAnim();  
};

#endif
