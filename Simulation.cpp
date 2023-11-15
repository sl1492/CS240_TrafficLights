#ifndef __Simulation_CPP__
#define __Simulation_CPP__
#include "Simulation.h"
#include <random>
#include <fstream>
#include <iostream>
using namespace std;

Simulation::Simulation(string file, int seed){
	this->seed = seed;
    ifstream infile;
    infile.open(file);

    if(!infile){
        cerr << "Error: could not open file: " << file << endl;
		exit(1);
	}
	string name;
	string value;

	// Reads the input file and stores variables in a loop;
	while (infile.good()){
		infile >> name >> value;
		if(name == "maximum_simulated_time:") {
			maxTime	 = stoi(value);
        }
		else if(name == "number_of_sections_before_intersection:") {
			sectionsBeforeIntersection = stoi(value);
        }
		else if(name == "green_north_south:") {
			nsGreen = stoi(value);
        }
		else if(name == "yellow_north_south:") {
			nsYellow = stoi(value);
        }
		else if(name == "green_east_west:") {
			ewGreen = stoi(value);
        }
		else if(name == "yellow_east_west:") {
			ewYellow = stoi(value);
        }
		else if(name == "prob_new_vehicle_northbound:") {
			pNewVehicleN = stod(value);
        }
		else if(name == "prob_new_vehicle_southbound:") {
			pNewVehicleS = stod(value);
        }
		else if(name == "prob_new_vehicle_eastbound:") {
            pNewVehicleE = stod(value);
        }
		else if(name == "prob_new_vehicle_westbound:") {
			pNewVehicleW = stod(value);
        }
		else if(name == "proportion_of_cars:") {
			Pcars = stod(value);
        }
		else if(name == "proportion_of_SUVs:") {
            Psuvs = stod(value);
        }
		else if(name == "proportion_right_turn_cars:") {
			pRCars = stod(value);
        }
		else if(name == "proportion_left_turn_cars:") {
			pLCars = stod(value);
        }
		else if(name == "proportion_right_turn_SUVs:") {
			pRSUVs = stod(value);
        }
		else if(name == "proportion_left_turn_SUVs:") {
			pLSUVs = stod(value);
        }
		else if(name == "proportion_right_turn_trucks:") {
			pRTrucks = stod(value);
        }
		else if(name == "proportion_left_turn_trucks:") {
			pLTrucks = stod(value);
        }
	}
	infile.close();
	Ptrucks = 1 - Pcars - Psuvs;
}


 // Destructor deletes every vehicle in the system
Simulation::~Simulation(){
	for (size_t i = 0; i < vehicleVector.size(); i++)
      delete vehicleVector[i];
	vehicleVector.clear();
}

// Function that animate the simulation
void Simulation::SetupAnim(){
	char dummy;
	Animator anim(sectionsBeforeIntersection);

    MSection ms1;
    MSection ms2;
    MSection ms3;
    MSection ms4;
	TrafficLight nsTrafficLight(nsGreen, nsYellow, ewGreen + ewYellow, LightColor::green);
    TrafficLight ewTrafficLight(ewGreen, ewYellow, nsGreen + nsYellow, LightColor::red);
    Road nbound(Direction::north, sectionsBeforeIntersection, &ms1, &ms2, &nsTrafficLight);
    Road wbound(Direction::west, sectionsBeforeIntersection, &ms2, &ms3, &ewTrafficLight);
    Road sbound(Direction::south, sectionsBeforeIntersection, &ms3, &ms4, &nsTrafficLight);
    Road ebound(Direction::east, sectionsBeforeIntersection, &ms4, &ms1, &ewTrafficLight);

	anim.setVehiclesNorthbound(nbound.getRoad());
    anim.setVehiclesWestbound(wbound.getRoad());
    anim.setVehiclesSouthbound(sbound.getRoad());
    anim.setVehiclesEastbound(ebound.getRoad());

	// Random number generator
    mt19937 rng;
    uniform_real_distribution<double> rand_double(0,1);
    rng.seed(seed);

	for (int i = 0; i <= maxTime; i++){
		// Create vehicles
		createVehicle(&nbound, pNewVehicleN, rand_double(rng), rand_double(rng), rand_double(rng));
		createVehicle(&wbound, pNewVehicleW, rand_double(rng), rand_double(rng), rand_double(rng));
		createVehicle(&sbound, pNewVehicleS, rand_double(rng), rand_double(rng), rand_double(rng));
		createVehicle(&ebound, pNewVehicleE, rand_double(rng), rand_double(rng), rand_double(rng));

		// Set trafficLight color
		anim.setLightNorthSouth(nsTrafficLight.getColor());
        anim.setLightEastWest(ewTrafficLight.getColor());

		// Set up lanes with animator
		anim.setVehiclesNorthbound(nbound.getRoad());
        anim.setVehiclesWestbound(wbound.getRoad());
        anim.setVehiclesSouthbound(sbound.getRoad());
        anim.setVehiclesEastbound(ebound.getRoad());
		anim.draw(i);

		// Wait for a button to be pressed
		cin.get(dummy);
		// Move traffic
		step();
		// Decrement time on trafficLights
		nsTrafficLight.decrementTimeLeft();
        ewTrafficLight.decrementTimeLeft();
	}
}

// Create a vehicle on a lane if there is place
void Simulation::createVehicle(Road *road, double roadProb, double createProb,
	double vehicleProb, double turnProb){

	// If it is possible to create a vehicle and probability is correct
	if((road->PossibleVeh()) && (createProb <= roadProb)){
		Vehicle *veh;

		// Create a car
		if(vehicleProb <= Pcars){
			if(turnProb <= pRCars)
				veh = new Vehicle(road, VehicleType::car, true);
			else
				veh = new Vehicle(road, VehicleType::car, false);
		}

		// Create an SUV
		else if(vehicleProb <= Pcars + Psuvs){
			if(turnProb <= pRSUVs)
				veh = new Vehicle(road, VehicleType::suv, true);
			else
				veh = new Vehicle(road, VehicleType::suv, false);
		}

		// Create a truck
		else{
			if(turnProb <= pRCars)
				veh = new Vehicle(road, VehicleType::truck, true);
			else
				veh = new Vehicle(road, VehicleType::truck, false);
		}

		// Push created vehicle into vehicleVector
		vehicleVector.push_back(veh);
	}
}


//Move traffic exactly by one section
void Simulation::step(){

	// Find indices of vehicles needed to be deallocated
	// It is needed if two consecutives vehicles will be deleted
	vector<int> indices;
	for (size_t i = 0; i < vehicleVector.size(); i++){
        if (vehicleVector[i]->reachedEnd())
			indices.push_back(i);
    }

	// Deallocate vehicles at correct indices
	for(size_t i = 0; i < indices.size(); i++){
		int index = indices[i] - i;
		// Create a pointer to a vehicle because deletes vector's memory otherwise
        Vehicle* vehiclePtr = vehicleVector[index];
        vehicleVector.erase(vehicleVector.begin() + index);
        delete vehiclePtr;
	}

	// Move every vehicle in the system
	for (size_t i = 0; i < vehicleVector.size(); i++)
		vehicleVector[i]->move();
}

// Main
int main(int argc, char* argv[]) {

    if(argc < 3){
        cerr << "Usage: ./sim [input file] [initial seed]" << endl;
        exit(1);
    }

    ifstream infile(argv[1]);
    if (!infile){
        cerr << "Error: could not open file: " << argv[1] << endl;
        exit(1);
    }

    int seed;
    try{
        seed = stoi(argv[2]);
    } catch(exception& e){
        cerr << "Invalid integer for the initial seed: " << argv[2] << endl;
        exit(1);
    }

    // Run simulation
    Simulation sim(argv[1], seed);
    sim.SetupAnim();

    return 0;
}

#endif