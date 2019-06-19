// Project Header files
#include "SimulatedTracker.hpp"

/**
*@brief Default constructor of the SimulatorVisualizer Class
*/
SimulatedTracker::SimulatedTracker(){

	// Initialize exitRequest to false
	this->exitRequest = false;
}

/**
*@brief Default destroyer of the SimulatorVisualizer Class
*/
SimulatedTracker::~SimulatedTracker(){}

/**
*@brief Start the tracking in the simulation functionality of the given tool
*@param the index of the tool list identifying the tool to be tracked
*/
std::thread SimulatedTracker::startToolTrackingInSimulation(const int toolID){

	std::thread trackThread(&PolarisProxy::enableTracking, &pp, toolID);

	return trackThread;

}