// Project Header files
#include "SimulatedTracker.hpp"
#include "PolarisProxy.hpp"
#include"SimulatorProxy.hpp"
#include"TechUserProxy.hpp"
#include <iostream>
using namespace std;

// NDI Header files
#include "CombinedApi.h"
#include "PortHandleInfo.h"
#include "ToolData.h"

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


void SimulatedTracker::configurePassiveTools()
{
	// Load a few passive tool definitions from a .rom files
	std::cout << std::endl << "Configuring Passive Tool - Loading .rom File..." << std::endl;

	const char* tool_location="../../sroms/8700340.rom";  //default value

	switch (sensor_type)
	{
	case 1:
		tool_location = "../../sroms/8700338.rom";
		cout << "chosen : 8700338.rom"<<endl;
		break;
	case 2:
		tool_location = "../../sroms/8700339.rom";
		cout << "chosen : 8700339.rom"<<endl;
		break;
	case 3:
		tool_location = "../../sroms/8700340.rom";
		cout << "chosen : 8700340.rom"<<endl;
		break;
		}

	pp.init();
	pp.loadTool( tool_location);
	pp.toolInitAndEnable();
	
}

void SimulatedTracker::send_data_vrep() {
	//Now Just need to send data to V-rep
	PolarisProxy getdata;

	transform_x = getdata.shared_tx; //assign sensor data to a variable and then assign it to vrep
	transform_y = getdata.shared_ty;
	transform_z = getdata.shared_tz;
}

/**
*@brief Start the tracking in the simulation functionality of the given tool
*@param the index of the tool list identifying the tool to be tracked
*/
std::thread SimulatedTracker::startToolTrackingInSimulation(const int toolID){

	std::thread trackThread(&PolarisProxy::enableTracking, &pp, toolID);


	return trackThread;

}


