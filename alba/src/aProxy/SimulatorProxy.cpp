#include "SimulatorProxy.hpp"
#include "SimulatedTracker.hpp"


/*
---------------------------------------------------------------------------------------------------------
For Connecting the project to V-Rep we should add following directories to 
the "Additional Include Directories"

C:\Program Files\V-REP3\V-REP_PRO_EDU\programming\remoteApi
C:\Program Files\V-REP3\V-REP_PRO_EDU\programming\include

also we should add theses lines to preprocessor definition in Project properties section:
(because extApi might get parsed/compiled before your file where you have the definition)

-   NON_MATLAB_PARSING
-   DO_NOT_USE_SHARED_MEMORY
-   MAX_EXT_API_CONNECTIONS=255
_   CRT_SECURE_NO_WARNINGS

more details: http://www.coppeliarobotics.com/helpFiles/en/remoteApiClientSide.htm
-----------------------------------------------------------------------------------------------
*/

#include <conio.h>
#include "windows.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


extern "C" {
#include "extApi.h"
}



/**
* @brief Default constructor of SimulatorProxy
*/
SimulatorProxy::SimulatorProxy() {

	this->connected = false;


}

// Load the chosen scense w.r.t tool .srom
int SimulatorProxy::load_scence(int tool_type) {

	//Load Scence of Vrep
	//  path = 'C:\Users\AHMAD\Downloads\My_Sample\Testing\vrepTest\Polaris_test.ttt';
	
	switch (tool_type) {
	case (1):
		system("start Polaris_Tool_1_Shortcut "); //open v-rep with appropriate Tool_1
		break;
	case (2):
		system("start Polaris_Tool_2_Shortcut "); //open v-rep with appropriate Tool_2
		break;
	case (3):
		system("start Polaris_Tool_3_Shortcut "); //open v-rep with appropriate Tool_3
		break;
	}
	return( tool_type);
}



int SimulatorProxy::connection_vrep() {

		//"continuous remote API server service"
		// Remember that v_repExtRemoteApi.dll plugin for V-rep's side loaded on startup
		//Check also remoteApiConnections.txt file for port configuration

		simxFinish(-1);                 //! Close any previously unfinished business
		int clientID = 0;
		Sleep(5000);
		
		simxChar* simulator_ip = "127.0.0.1";  // IP Address which the vrep can be found
		//clientID = simxStart((simxChar*)"127.0.0.1", 19997, true, true, 5000, 5);  //!< Main connection to V-REP
		clientID = simxStart(simulator_ip, 19997, true, true, 5000, 5);
																				   // wait 5 seconds to connect to vrep
		cout << "ClientID=" << clientID << "\n";

		Sleep(1000);
		if (clientID != -1)  // if Connection status is OK
		{
			
			cout << " Connection with V-REP established" << endl;
			simxInt syncho = simxSynchronous(clientID, true);  //Synchronous with client

			int sim_status;
			sim_status = simxStartSimulation(clientID, simx_opmode_oneshot); //start simulation in V-rep 
			cout << "Simulation status: " << sim_status << endl;
			if (sim_status == 1) {

				cout << "Simulation Started ..." << endl;
			}
			else {
				cout << "Simulation Not Started ..." << endl;
			}

			int polaris_probe = 0;
			simxGetObjectHandle(clientID, "Shape", &polaris_probe, simx_opmode_oneshot_wait);  // Get Shape(RigidBody)
			cout << "Now Move the Rigid Body to see the tracking results:" << endl;
			
			double x, y ,z;  //X ,Y,Z position

			SimulatedTracker recieved_data;
			while (1) {
				x = recieved_data.toVrep_x;  //Assign recieved data from SimulatedTracker to Vrep position variables
				y = recieved_data.toVrep_y;
				z = recieved_data.toVrep_z;
				const simxFloat my_position[3] = { x,y,z }; //position of Object(Shape) in  X,Y,Z format inside Vrep

				simxSetObjectPosition(clientID, polaris_probe, -1, my_position, simx_opmode_oneshot_wait);  // Set new Object Position
			}

			Sleep(1000);
			simxPauseCommunication(clientID, 0);
		}

		else
		{
			cout << " Connection status to VREP: FAILED" << endl;
		}
		simxFinish(clientID);

		return(0);
}

/**
* @brief Default destroyer of SimulatorProxy
*/
SimulatorProxy::~SimulatorProxy(){

}

/**
*@brief Initialization function
*/
void SimulatorProxy::init(){}

/**
*@brief Verify if the sensor is properly connected to the system and ready for communication (set available flag)
*@return flag stating if the sensor is present 
*/
void SimulatorProxy::checkConnection(){


}


/**
*@brief Error Connection Message of the sensor
*@return the message string
*/
char* SimulatorProxy::errorConnectionMessage(){


	return "[SIMULATOR] Simulator not detected. Cannot run the required functionalities.";

}