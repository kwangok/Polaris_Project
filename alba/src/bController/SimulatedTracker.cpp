// Project Header files
#include "SimulatedTracker.hpp"
#include "PolarisProxy.hpp"
#include"SimulatorProxy.hpp"
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



void SimulatedTracker::get_sensor_data(const ToolData& toolData) {
	PolarisProxy sensor_data;
	double zero,x, y, x,z;
	zero=sensor_data.sensor_0;
	x = sensor_data.sensor_x;
	y = sensor_data.sensor_y;
	z = sensor_data.sensor_z;

	//Send Data to Vrep 
	//Scaling maybe required
	 SimulatedTracker::toVrep_0=zero;
	 SimulatedTracker::toVrep_x=x;
	 SimulatedTracker::toVrep_y=y;
	 SimulatedTracker::toVrep_z=z;


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












// Recieve Position Data from Polaris sensor

/*
The API Commnads which should be initialized till framework starts to recieve position data

// First check flowchart in page-26

1---> "INIT" ----> Initializes the system.

2--->"PHSR" ---->Returns the number of assigned port handles and the port status for each one. Assigns a port handle
to a wired tool, GPIO device, or strober

3--->"PHINF"--->Returns port handle status, information about the tool associated with the port handle, and the
physical location of a port handle.

4---> "PHRQ" ---->Assigns a port handle to a tool or GPIO device.
5--->"PVWR" ----> Assigns a tool definition file to a wireless tool, or overrides the SROM device in a wired tool or GPIO device.

6---> "PINIT" ----> Initializes a port handle

7--->"PENA"--->Enables the reporting of transformations for a particular port handle.

8---> Load the Tool(.srom file)

//Here we have 3 options:

8a --->"3D" ---->Returns the latest three-dimensional marker position of a single marker or multiple markers.
8b --->"BX" ---->Returns the latest tool transformations, individual marker positions, and system status in binary format.
8c --->"TX" ---->Returns the latest tool transformations, individual marker positions, and system status in text format.



note:  a port handle must be initialized (PINIT) before it can be enabled (PENA).

-Commands must be sent from the host computer to the system in one of the two following formats.
<Command><SPACE><Parameter1><Parameter2>...<ParameterN><CR>

-If a complete command is received by the system, replies are sent back in the format:
<Reply><CRC16>

*/


/*
These functions located in CombinedApi.cpp file

1. INIT ---->  CombinedApi::initialize()
2.PHSR ----> CombinedApi::portHandleSearchRequest()
3.PHINF ---->CombinedApi::portHandleInfo()
3a.PHF ----> portHandleFree()
4.PHRQ ---->CombinedApi::portHandleRequest()
5.PINIT----> CombinedApi::portHandleInitialize()
6.PENA---->CombinedApi::portHandleEnable()
7.PVWR---->CombinedApi::loadSromToPort()
8. Start to Track  ---->startTracking()
9.Stop Tracking ---->stopTracking()
10.Get Data (TX) ---->getTrackingDataTX()
11.Get Data (BX) ---->getTrackingDataBX()
12.Get Data (BX2) ---->getTrackingDataBX2()
13. Get Errors or warning messages -----> getErrorString() ----------  getWarningString()  -------getErrorCodeFromResponse()
14.Reads the response from the device ----> readResponse()

-note that for processing the errors/warnings or reply we could use this convertion functions:
A) string intToString()    B) stringToInt()    C) errorToString()

---------------------------------------------------------------------------------------------
These functions located in MarkerData.cpp file
-Marker status---->MarkerStatus() ---->"OK , MissingOutOfVolume ,Saturated ,..."
-markerIndex
-The marker position (x,y,z) [mm] ---->double x,y,z

--------------------------------------------------------------------------------------------
These functions are in portHandleInfo.cpp

Returns the port handle as a string---->getPortHandle()
Returns the tool's revision number---->getRevision()
Return the status as a string ----> getStatus()
------------------------------------------------------------------------------------------
These functions are in GbfData3D.cpp
"This class encapsulates 3D marker data as it is read from BX2"

GbfData3D::GbfData3D(BufferedReader& reader,  int numberOfTools)

-Read the data--->toolHandle = reader.get_uint16(); 		numberOf3Ds = reader.get_uint16();

Put the toolHandle into its own vector ---->toolHandles.push_back(toolHandle);

Create a corresponding vector with the 3Ds -----> std::vector<MarkerData> list3Ds;

pos.x = reader.get_double();
pos.y = reader.get_double();
pos.z = reader.get_double();

*/