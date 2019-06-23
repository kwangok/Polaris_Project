#include "PolarisProxy.hpp"
#include "SimulatorProxy.hpp"


#include <vector>


#ifdef DEBUG
	#include <iostream>
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**
* @brief Constructor of PolarisProxy with Port Number argument
*/
PolarisProxy::PolarisProxy(){}

/**
* @brief Default destroyer of PolarisProxy
*/
PolarisProxy::~PolarisProxy(){

	// Delete the dynamic pointer to the NDI Class
	delete capi;

}


/**
*@brief Initialization function
*/
void PolarisProxy::init(){

	// Dynamic instance of NDI Combined API Class
	capi = new CombinedApi();

	// Initialize the connected flag to false
	this->connected = false;

	// Initialize the BX2 support flag to false // TODO: Check what is the difference with BX
	this->apiSupportsBX2 = false;

	// Initialize the tracking flag
	this->tracking = false;

	// Check the connection with the Polaris sensor
	checkConnection();

	if (this->connected){
		// Check the BX2 support for the current API version
		determineApiSupportForBX2();

		// Send the INIT command to the Polaris Sensor (aka Initialize the communication)
		int ret = capi->initialize();

#ifdef DEBUG
		std::cout << "Polaris Sensor " << ((ret == 0) ? "initialized successfully." : "not initialized. Error in initialize() function.") << std::endl;
#endif // DEBUG

	}
}



/**
*@brief Verify if the sensor is properly connected to the system and ready for communication (set available flag)
*/
void PolarisProxy::checkConnection(){

	// Try to connect
	if (capi->connect(this->serialPort) != 0){
#ifdef DEBUG
		std::cout << "Connection to Serial Port " << this->serialPort << " failed. Trying another port..." << std::endl;
#endif
	}
	else{
#ifdef DEBUG
		std::cout << "Connected to Serial Port " << this->serialPort << "!" << std::endl;
#endif
		this->connected = true;
	}
	

}


/**
* @brief Determines whether an NDI device supports the BX2 command by looking at the API revision
*/
void PolarisProxy::determineApiSupportForBX2()
{
	// Lookup the API revision
	std::string response = capi->getApiRevision();

	// Refer to the API guide for how to interpret the APIREV response
	char deviceFamily = response[0];
	int majorVersion = capi->stringToInt(response.substr(2, 3));

	// As of early 2017, the only NDI device supporting BX2 is the Vega
	// Vega is a Polaris device with API major version 003
	if (deviceFamily == 'G' && majorVersion >= 3)
	{
		this->apiSupportsBX2 = true;
#ifdef DEBUG
		std::cout << "This API version supports BX2." << std::endl;
#endif // DEBUG
	}
	else{
#ifdef DEBUG
		std::cout << "This API version DOES NOT support BX2." << std::endl;
#endif // DEBUG
	}
}



/**
*@brief Enable the tracking of a specific given tool
*@param index of the tool list
*/


void PolarisProxy::onErrorPrintDebugMessage(std::string methodName, int errorCode)
{
	if (errorCode < 0)
	{
		std::cout << methodName << " failed: " << capi->errorToString(errorCode) << std::endl;
	}
}


void PolarisProxy::printToolData(const ToolData& toolData)
{
	if (toolData.systemAlerts.size() > 0)
	{
		std::cout << "[" << toolData.systemAlerts.size() << " alerts] ";
		for (int a = 0; a < toolData.systemAlerts.size(); a++)
		{
			std::cout << toolData.systemAlerts[a].toString() << std::endl;
		}
	}
}






 //@brief Returns a string representation of the data in CSV format.
 //@details The CSV format is : "Frame#,ToolHandle,Face,TransformStatus,q0,qx,qy,qz,tx,ty,tz,error,#markers,[Marker1:status,x,y,z],[Marker2..."
 
std::string toolDataToCSV(const ToolData& toolData)
{
	std::stringstream stream;
	stream << std::setprecision(toolData.PRECISION) << std::setfill('0');
	stream << "" << static_cast<unsigned>(toolData.frameNumber) << ","
		<< "Port:" << static_cast<unsigned>(toolData.transform.toolHandle) << ",";
	if (toolData.transform.isMissing())
	{
		stream << "Missing,,,,,,,,";
	}
	else
	{
		stream << static_cast<unsigned>(toolData.transform.getFaceNumber()) << ","
			<< TransformStatus::toString(toolData.transform.getErrorCode()) << ","
			<< toolData.transform.q0 << "," << toolData.transform.qx << "," << toolData.transform.qy << "," << toolData.transform.qz << ","
			<< toolData.transform.tx << "," << toolData.transform.ty << "," << toolData.transform.tz << "," << toolData.transform.error;

		PolarisProxy sensor_data;
		sensor_data.sensor_0 = toolData.transform.q0;      //quaternion parameters in camera coordinates [mm]
		sensor_data.sensor_x = toolData.transform.qx;      //x position of Polaris Sensor
		sensor_data.sensor_y = toolData.transform.qy;     //y position of Polaris Sensor
		sensor_data.sensor_z = toolData.transform.qz;    //z position of Polaris Sensor

		sensor_data.sensor_tx = toolData.transform.qx;      // x transformation parameters in camera coordinates [mm]
		sensor_data.sensor_ty = toolData.transform.qy;     //y  transformation parameters in camera coordinates [mm]
		sensor_data.sensor_tz = toolData.transform.qz;    //z transformation parameters in camera coordinates [mm]

	}

	// Each marker is printed as: status,tx,ty,tz
	stream << "," << toolData.markers.size();
	for (int i = 0; i < toolData.markers.size(); i++)
	{
		stream << "," << MarkerStatus::toString(toolData.markers[i].status);
		if (toolData.markers[i].status == MarkerStatus::Missing)
		{
			stream << ",,,";
		}
		else
		{
			stream << "," << toolData.markers[i].x << "," << toolData.markers[i].y << "," << toolData.markers[i].z;
		}
	}
	return stream.str();
}








void PolarisProxy::enableTracking(const int& toolID) {

#ifdef DEBUG
	std::cout << "Inside the Polaris Proxy thread. Doing nothing and exiting ... " << std::endl;
#endif // DEBUG

	//get traking Data Bx
	//Reply Option		m Data---->The data specific to the requested reply option. 
	//the data stored in a vector called ToolData

	//After get data , it should be stored in a variable and then called in Simulator Tracker 
	for (int i = 0; i < 10; i++)
	{
		// Start tracking, output a few frames of data, and stop tracking
		std::cout << std::endl << "Entering tracking mode and collecting data..." << std::endl;
		onErrorPrintDebugMessage("capi.startTracking()", capi->startTracking());    //start tracking
		for (int i = 0; i < 10; i++)
		{

			// Demonstrate BX command
			toolData = capi->getTrackingDataBX();

			// Print to stdout in similar format to CSV
			std::cout << "[alerts] [buttons] Frame#,ToolHandle,Face#,TransformStatus,Q0,Qx,Qy,Qz,Tx,Ty,Tz,Error,#Markers,State,Tx,Ty,Tz" << std::endl;
			for (int i = 0; i < toolData.size(); i++)
			{
				printToolData(toolData[i]);
			}
		}
		// Stop tracking (back to configuration mode)
		std::cout << std::endl << "Leaving tracking mode and returning to configuration mode..." << std::endl;
		onErrorPrintDebugMessage("capi.stopTracking()", capi->stopTracking());

	}
}
#ifdef DEBUG
		std::cout << "[PP] Fake tracking (tracking: " << this->tracking << ")... " << std::endl;
#endif // DEBUG



#ifdef DEBUG
	std::cout << "[PP] Exiting... " << std::endl;
#endif // DEBUG






void PolarisProxy::configureUserParameters()
{
#ifdef DEBUG
	std::cout << capi->getUserParameter("Param.User.String0") << std::endl;
#endif
	capi->setUserParameter("Param.User.String0", "customString");
#ifdef DEBUG
	std::cout << capi->getUserParameter("Param.User.String0") << std::endl;
#endif
	capi->setUserParameter("Param.User.String0", "");
}


void PolarisProxy::loadTool(const char* toolDefinitionFilePath){

	// Request a port handle to load a passive tool into
	int portHandle = capi->portHandleRequest();

#ifdef DEBUG
	std::cout << "Polaris portHandle: " << portHandle << std::endl;
#endif // DEBUG


	// Load the .rom file using the previously obtained port handle
    capi->loadSromToPort(toolDefinitionFilePath, portHandle);

#ifdef DEBUG
	std::cout << "Tool loaded." << std::endl;
#endif // DEBUG


}


/**
* @brief Initialize and enable the loaded tools
*/
void PolarisProxy::toolInitAndEnable(){

	// Initialize and enable tools
	std::vector<PortHandleInfo> portHandles = capi->portHandleSearchRequest(PortHandleSearchRequestOption::NotInit);
	for (int i = 0; i < portHandles.size(); i++)
	{
		capi->portHandleInitialize(portHandles[i].getPortHandle());
		capi->portHandleEnable(portHandles[i].getPortHandle());
	}

	// Print all enabled tools
	portHandles = capi->portHandleSearchRequest(PortHandleSearchRequestOption::Enabled);
#ifdef DEBUG
	for (int i = 0; i < portHandles.size(); i++)
	{
		std::cout << portHandles[i].toString() << std::endl;
	}
#endif // DEBUG


}




/**
* @brief Print Tracking data
*/
void PolarisProxy::trackingDataPrint(){

	 
}



/**
*@brief Error Connection Message of the sensor
*@return the message string
*/
char* PolarisProxy::errorConnectionMessage(){


	return "[POLARIS] Simulator not detected. Cannot run the required functionalities.";

}




