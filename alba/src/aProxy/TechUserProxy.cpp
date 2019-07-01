// System Header files
#ifdef DEBUG
#include <iostream>
#endif
#include <iostream>

// Project Header files
#include "TechUserProxy.hpp"
#include "SimulatedTracker.hpp"

/**
* @brief Default constructor of TechUserProxy
*/
TechUserProxy::TechUserProxy(){

	// Set the User type (UserProxy interfaces with Technician User)
	this->userType = TECH_USER;

}

/**
* @brief Default destroyer of TechUserProxy
*/
TechUserProxy::~TechUserProxy(){}

/**
* @brief Allow selection of the action for the user
* @param the code of the chosen option
* @param the set of input arguments passed to the program
* @return forward the code of the chosen option
*/
int TechUserProxy::sendRequest(const int& req, const char** argv){

	// Print Menu options
	UserProxy::sendRequest(req, argv);
	
	if (req == TRACK_SIMULATOR){
		this->requestForTrackSimulator(argv);
	}

	return req;

}

/**
* @brief Method that forwards the request to track the Polaris markers and show them in the simulator
* @param the set of input arguments passed to the program
*/
bool TechUserProxy::requestForTrackSimulator(const char** argv){

	// Variables initialization
	bool ret = false;
	std::vector<std::string> toolNames;
	int toolOption = NULL;

#ifdef DEBUG
	std::cout << "[U] Forwarding Simulator procedure request ... " << std::endl;
#endif

	// Create a static instance of the coordinator class SimulatedTracker
	SimulatedTracker simTrack;

	// 0a. Connect to the devices (in this point presence check is already done)
	// Convention: the input passed arguments are: 1: Polaris Serial Port ; 2: V-REP IP Address
	simTrack.setPolarisPort(std::string(argv[1]));
	simTrack.setSimIP(std::string(argv[2]));

	// 0b. Acquire the list of tool names
	toolNames = simTrack.getSensorToolNames();

	// 1. Let the User choose the tool to load
	while (toolOption == NULL || (toolOption <= 0 || toolOption > toolNames.size())) {

		// Raise error message in case of wrong input
		if (toolOption != NULL){
			std::cout << "Error: " << wrongToolOptionMessage() << std::endl;
		}
		
		std::cout << "Select the tool that you want to track: \n" << std::endl;
		for (int i = 0; i < toolNames.size(); i++){
			std::cout << "\t " << i + 1 << ": " << toolNames[i] << std::endl;
		}

		// Acquire input from the user
		std::cin >> toolOption;

	}

	// 2. Load tools on Polaris and V-REP sides

	int tool_type = toolOption;
	simTrack.sensor_type = tool_type;  //Load srom file inside SimulatedTracker

	simTrack.configurePassiveTools(); // Configure / Load tool on Polaris side
		
	
	// 3. Run the SimulatedTracker functionality on a separate thread
	std::thread trackThread = simTrack.startToolTrackingInSimulation(toolOption);

	// 4. Wait for exit request from the user
	std::cout << "Tracking started. \n"
		"Press ESC when you want to stop tracking... " << std::endl;

	while (!simTrack.isExitRequested()){
	
		if (_kbhit()){ // Keyboard hit utility function

			// Acquire hit character
			int key = _getch();

			// If ESCAPE bar hit
			if (key == ESCAPE){
#ifdef DEBUG
				std::cout << "\nTerminating the Tracking in Simulation mode...";
#endif //DEBUG
				// 5. Send the exit request to the SimulatedTracker thread
				simTrack.exit();
			}
		}
	}

	std::cout << "done." << std::endl;
	std::cout << "Waiting for thread to return ... ";
#ifdef DEBUG
	std::cout << "done." << std::endl;
	std::cout << "Waiting for thread to return ... ";
#endif //DEBUG

	// 6. Join the threads
	trackThread.join();

#ifdef DEBUG
	std::cout << "done." << std::endl;
#endif //DEBUG

	return ret;
}


/**
* @brief Check the validity of the option chosen by the user in the Menu
* @param the code of the chosen option
* @return a flag indicating the validity
*/
bool TechUserProxy::checkOptionValidity(const int& op){

	return UserProxy::checkOptionValidity(op) || (op == TRACK_SIMULATOR);

}
