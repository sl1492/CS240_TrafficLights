# CS240_TrafficLights
CS240 Final Project - Software Systems - C++

In this project, we created Section.h, Section.cpp, MSection.h, MSection.cpp, TrafficLight.h, 
TrafficLight.cpp, Vehicle.h, Vehicle.cpp, Road.h, Road.cpp, Simulation.h and Simulation.cpp to 
implement a traffic intersection simulation. The lane is composed of three classes: "Section", 
"MSection", and "Road". "Section" is the base unit on the lane, and "MSection" deals with the 
intersection. "Road" is consisted of "Section", "MSection", and "Light". We also created 4 buffers
on the "Road" to load vehicles before they enter the bound. 

For the "Vehicle" class, it is a subclass of "VehicleBase". We added the movements on the Vehicle, 
and make it move forward / turnright on the road. All traffic rules are implemented in the "Vehicle" 
class. For the "Light" class, we defined three colors and duration for each light. We also measure
the timeleft for each color and change the color when time decremented to zero. In the "Simulation" 
class, we read in the input file and create different objects for the implementation of traffics.

We compile the program by using the Makefile to create executable called "sim". 
We compile and run the program with the following lines of code:

% make 
% ./sim [input file] [initial seed]

our input file is named as "input.txt"
