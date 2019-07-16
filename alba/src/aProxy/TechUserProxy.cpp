#include "SimulatedTracker.hpp"

// System Header files
#include <iostream>

// Project Header files
#include "TechUserProxy.hpp"
#include "KeyboardHandler.hpp"
#include "Timer.hpp"

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

#ifdef DEBUG
	std::cout << "[U] Forwarding Simulator procedure request ... " << std::endl;
#endif

	// Variables initialization
	double dt, et, rate, tic, toc, tac, Ts;
	bool ret = false;
	std::vector<std::string> toolNames;
	std::string polarisShdMemName;
	int toolOption = NULL;
    int key = 0;
    bool kbhitFlag = false;
	double* data;
	KeyboardHandler kb;
	Timer clock;

	// Create a static instance of the coordinator class SimulatedTracker
	SimulatedTracker simTrack;

	// Get the clock rate
	rate = clock.getRate();
	Ts = 1.0 / rate;

	// 1. Initialize the required external systems (Polaris Sensor and V-REP simulators)
	initExtSystems(&simTrack, argv);

	// 2. Request for the Polaris tool type
	std::vector<std::string> polarisToolList = simTrack.getSensorToolNames();
	toolOption = chooseFromList(polarisToolList);

	// 3. Create a shared memory to share data with the Polaris thread, before its creation
	simTrack.createShdMem();

	// 4. Launch parallel thread to share data
	std::thread trackThread = simTrack.startToolTracking(toolOption);

	std::cout << "Tracking started. Press ESC when you want to stop tracking... " << std::endl;
	// 5. Wait for exit request from the user
	while (!simTrack.isExitRequested()){
	
		// Measure starting time
		tic = clock.getCurTime();

		//----------------------------------------------------------------//
		// Do stuff here... 

		// If a key is pressed ...
		kbhitFlag = kb.kbhit();
		if (kbhitFlag){

			// Get the current value
			key = kb.getChar();

			// If the key is ESC, terminate
			if (key == ESCAPE){
				// 6. Send the exit request to the thread and exit
				simTrack.exit();
			}
		}

		// 7. Read data from shared memory
		data = simTrack.readDataFromShdMem();

		// Print acquired data
		//this->printToolData(data);

		//Send Data to SimulatedTracker 
		simTrack.sendDataToSimProxy(data);
		//----------------------------------------------------------------//

		// Measure the ending time and the elapsed time
		toc = clock.getCurTime();
		dt = clock.elapsedTime(tic, toc);

		// Wait until Ts
		if (dt < Ts){
			clock.timeSleep(Ts - dt);
		}

		// Measure the final time after sleep to check the actual rate of the thread
		tac = clock.getCurTime();
		et = clock.elapsedTime(tic, tac);

#ifdef DEBUG
		std::cout << "[TUP] Running rate " << 1.0/et << " Hz" << std::endl;
#endif // DEBUG
	}


#ifdef DEBUG
	std::cout << "done." << std::endl;
	std::cout << "Waiting for thread to return ... ";
#endif //DEBUG

	// N. Remove the shared memory
	simTrack.removeShdMem();

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

void TechUserProxy::initExtSystems(SimulatedTracker* trackPtr, const char** argv){

	// 1-4. Initialize the Polaris sensor and let the user choose the tool to use
	UserProxy::initExtSystems(trackPtr, argv);

	// 5. Set the IP address of the V-REP simulator
	trackPtr->setSimIP(std::string(argv[2]));

	// 6. Connect the V-REP simulator
	trackPtr->initVREP();

}
