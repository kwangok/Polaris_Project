#ifndef POLARISPROXY_HPP_
#define POLARISPROXY_HPP_

// NDI Header files
#include "CombinedApi.h"
#include "PortHandleInfo.h"
#include "ToolData.h"

// Project Header files
#include "SensorProxyInterface.hpp"


class PolarisProxy : public SensorProxyInterface {

public:

	/**
	* @brief Constructor of PolarisProxy with Port Number argument
	*/
	PolarisProxy();

	/**
	* @brief Default destroyer of PolarisProxy
	*/
	~PolarisProxy();

	/**
	*@brief Initialization function
	*/
	void init();

	/**
	* @brief Determines whether an NDI device supports the BX2 command by looking at the API revision
	*/
	void determineApiSupportForBX2();

	/**
	* @brief Sample function for User Parameters configuration
	*/
	void configureUserParameters();

	/**
	*@brief Error Connection Message of the sensor
	*@return the message string
	*/
	char* errorConnectionMessage();

	/**
	* @brief Loads a tool from a tool definition file (.rom)
	*/
	void loadTool(const char* toolDefinitionFilePath);

	/**
	* @brief Initialize and enable the loaded tools
	*/
	void toolInitAndEnable();





	/**
	* @brief Print Tracking data
	*/
	void trackingDataPrint();

	/**
	 *@brief Set function. Set the serial port of the Polaris
	*/
	inline void setPort(const std::string& port_){ this->serialPort = port_; }

	/**
	*@brief Enable the tracking of a specific given tool
	*@param index of the tool list
	*/
	void enableTracking(const int& toolID);


	void onErrorPrintDebugMessage(std::string methodName, int errorCode);


	std::vector<ToolData> toolData;  // variable toolData 

	double  sensor_0, sensor_x, sensor_y, sensor_z;
	double   sensor_tx, sensor_ty, sensor_tz;

	void printToolData(const ToolData& toolData);

	std::string toolDataToCSV(const ToolData& toolData);


	/**
	*@brief Stop the running tracking 
	*/
	inline void stopTracking() { this->tracking = false; }

private:

	CombinedApi* capi;					//!< Dynamic instance of NDI Combined Class
	std::string serialPort;				//!< String storing the Serial COM port on which the Sensor is connected
	bool apiSupportsBX2;				//!< If the APIs support BX2 or not (based on the revision number)
	bool tracking;						//!< If the Polaris Sensor is tracking 

	
	/**
	*@brief Verify if the sensor is properly connected to the system and ready for communication (set available flag)
	*@return flag stating if the sensor is present
	*/
	void checkConnection();

};


#endif //POLARISPROXY_HPP_