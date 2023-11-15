#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //For reverse()
using namespace std;

int main(int argc, char* argv[]) {
    ifstream infile{argv[1]};
    if(!infile){
        cerr << "Error: could not open file: " << argv[1] << endl;
		exit(1);
	}
	string name;
	string value;

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

    cout << "max time:" << maxTime << endl;
    cout << ewGreen << endl;
    cout << ewYellow << endl;
    cout << nsYellow << endl;
    cout << nsGreen << endl;

    // cout << maxTime << endl;
    // cout << maxTime << endl;
    // cout << maxTime << endl;

}
