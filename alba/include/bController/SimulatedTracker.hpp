#ifndef SIMULATED_TRACKER_HPP_
#define SIMULATED_TRACKER_HPP_

// System Header files
#include <string>
#include <thread>

// Project Header files
#include "PolarisProxy.hpp"
#include "SimulatorProxy.hpp"

class SimulatedTracker{

public:

	/**
	*@brief Default constructor of the SimulatorVisualizer Class
	*/
	SimulatedTracker();

	/**
	*@brief Default destroyer of the SimulatorVisualizer Class
	*/
	~SimulatedTracker();

	/**
	*@brief Send the request to close the thread for tracking in simulation
	*/


	void get_sensor_data(const ToolData& toolData);

	double  sensor_0, sensor_x, sensor_y, sensor_z;
	double  toVrep_0, toVrep_x,toVrep_y,toVrep_z;


	inline void exit(){ pp.stopTracking(); this->exitRequest = true; }

	/**
	*@brief Check if the exitRequest flag is set
	*@return the exitRequest flag
	*/
	inline bool isExitRequested(){ return this->exitRequest; }

	/**
	*@brief Start the tracking in the simulation functionality of the given tool
	*@param the index of the tool list identifying the tool to be tracked
	*/
	std::thread startToolTrackingInSimulation(const int toolID);

	/**
	*@brief Set function. Set the serial port for the Polaris Proxy
	*@param the serial port string
	*/
	inline void setPolarisPort(const std::string& port_){ pp.setPort(port_); }

	/**
	*@brief Set function. Set the simulation port for the V-REP simulator
	*@param the simulator port
	*/
	inline void setSimIP(const std::string& ip_){ sp.setIP(ip_); }

	/**
	*@brief Get function. Get the list of tool names from one of the Sensor Proxy
	*@return the list of sensor tool names
	*/
	inline std::vector<std::string> getSensorToolNames() { return pp.getToolNameList(); };


private:

	bool exitRequest;			//!< Flag set by the user to request the end of the tracking in the simulation
	PolarisProxy pp;			//!< Static instance of the PolarisProxy class
	SimulatorProxy sp;			//!< Static instance of the SimulatorProxy class

};


#endif //SIMULATED_TRACKER_HPP_