#ifndef TRACKER_HPP_
#define TRACKER_HPP_

// Project Header files
#include "PolarisProxy.hpp"
#include "Applicator.hpp"

class Tracker{

public:

	/**
	*@brief Default constructor of the Tracker Class
	*/
	Tracker();

	/**
	*@brief Default destroyer of the Tracker Class
	*/
	~Tracker();

	/**
	*@brief Send the request to close the thread for tracking
	*/
	inline void exit(){ pp.stopTracking(); this->exitRequest = true; }

	/**
	*@brief Check if the exitRequest flag is set
	*@return the exitRequest flag
	*/
	inline bool isExitRequested(){ return this->exitRequest; }

	/**
	*@brief Set function. Set the serial port for the Polaris Proxy
	*@param the serial port string
	*/
	inline void setPolarisPort(const std::string& port_){ pp.setPort(port_); }

	/**
	*@brief Set function. Set the serial port for the Polaris Proxy
	*@param the serial port string
	*/
	inline void initPolaris(){ pp.init(); }

	/**
	*@brief Get function. Get the list of tool names from one of the Sensor Proxy
	*@return the list of sensor tool names
	*/
	inline std::vector<std::string> getSensorToolNames() { return pp.getToolNameList(); };

	/**
	*@brief Get function. Get the list of applicators available
	*@return the list of applicators
	*/
	inline std::vector<std::string> getApplicatorList() { return ap.getNamesList(); };

	/**
	*@brief Start the tracking of the given tool
	*@param the index of the tool list identifying the tool to be tracked
	*/
	std::thread startToolTracking(const int toolID);

protected:

	bool exitRequest;			//!< Flag set by the user to request the end of the tracking
	PolarisProxy pp;			//!< Static instance of the PolarisProxy class
	Applicator ap;				//!< Static instance of an Applicator class


};

#endif //TRACKER_HPP_