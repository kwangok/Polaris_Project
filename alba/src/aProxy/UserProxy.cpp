#ifdef DEBUG
// System Header files
#include <iostream>
#endif

// Project Header files
#include "UserProxy.hpp"

UserProxy::UserProxy(){
	
	// Set the User type (UserProxy interfaces with Generic User)
	this->userType = GENERIC_USER;

}

UserProxy::~UserProxy(){} 


/**
* @brief Allow selection of the action for the user
* @param the code of the chosen option
* @param the set of input arguments passed to the program
* @return forward the code of the chosen option
*/
int UserProxy::sendRequest(const int& req, const char** argv){
	// Execute the corresponding action, based on the user's choice
	if (req == PAIRING){ // Start Pairing procedure
		this->requestForPairing();
	}
	else if (req == REGISTRATION){ // Start Registration procedure
		this->requestForRegistration(argv);
	}
	else if (req == POSITIONING){ // Start Computer-Assisted procedure
		this->requestForComputerAssistedPositioning();
	}

	return req;
}

/**
* @brief Method that forwards the request to start the Pairing procedure
*/
bool UserProxy::requestForPairing(){
	
	bool ret = false;

#if DEBUG
	std::cout << "[U] Forwarding Pairing procedure request ... " << std::endl;
#endif

	return ret;
}

/**
* @brief Method that forwards the request to start the Registration procedure
*/
bool UserProxy::requestForRegistration(const char** argv){

	bool ret = false;

#if DEBUG
	std::cout << "[U] Forwarding Registration procedure request ... " << std::endl;
#endif
	
	// 0. Init variables
	int collectedPoints = 0;
	bool exitCondition = false;
	bool threadBased = false;

	// 1. Let the Controller init the Sensor

	// 2. If sensorOk, send three inputs from keyboard
	// 2.1 Run until you collect 3 repere points, OR user requests for exit
	// 2.2 If Space bar hit
	// 2.2.1 Save 
	// 2.2 If the acquired point is valid ...
	// 2.3 ... increase the counter of collected points
	// 3. If thread-based, let the Controller close the Sensor

	return ret;

}

/**
* @brief Method that forwards the request to start the Computer-Assisted Positioning procedure
*/
bool UserProxy::requestForComputerAssistedPositioning(){

	bool ret = false;

#if DEBUG
	std::cout << "[U] Forwarding Computer-Assisted procedure request ... " << std::endl;
#endif

	return ret;
}

/**
* @brief Check the validity of the option chosen by the user in the Menu
* @param the code of the chosen option
* @return a flag indicating the validity
*/
bool UserProxy::checkOptionValidity(const int& op){

	return (op == PAIRING || op == REGISTRATION || op == POSITIONING);

}


