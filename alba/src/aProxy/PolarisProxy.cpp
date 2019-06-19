#include "PolarisProxy.hpp"

#ifdef DEBUG
	#include <iostream>
#endif

#include <iostream>

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
void PolarisProxy::enableTracking(const int& toolID){

#ifdef DEBUG
	std::cout << "Inside the Polaris Proxy thread. Doing nothing and exiting ... " << std::endl;
#endif // DEBUG

	this->tracking = true;

	while (this->tracking){
	
#ifdef DEBUG
		std::cout << "[PP] Fake tracking (tracking: " << this->tracking << ")... " << std::endl;
#endif // DEBUG

	}

#ifdef DEBUG
	std::cout << "[PP] Exiting... " << std::endl;
#endif // DEBUG


}



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