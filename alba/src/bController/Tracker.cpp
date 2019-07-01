// Project header files
#include "Tracker.hpp"

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

/**
*@brief Default constructor of the Tracker Class
*/
Tracker::Tracker(){

	// Initialize exitRequest to false
	this->exitRequest = false;

}

/**
*@brief Default destroyer of the Tracker Class
*/
Tracker::~Tracker(){}

/**
*@brief Start the tracking of the given tool
*/
std::thread Tracker::startToolTracking(const int toolID){

	std::thread th;

	// 1. Build the string for the path of the tool to load
	std::vector<std::string> toolList = pp.getToolNameList();
	std::string pathString = "./sroms/";
	std::string toolPath = pathString + toolList[toolID-1];

#ifdef DEBUG
	std::cout << "toolPath: " << toolPath << std::endl;
#endif // DEBUG

	// 2. Load the tool on the Polaris
	pp.loadTool(toolPath.c_str());

	std::thread trackThread(&PolarisProxy::enableTracking, &pp);

	return trackThread;
}
