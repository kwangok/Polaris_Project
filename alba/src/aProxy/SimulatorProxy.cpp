
#include "SimulatorProxy.hpp"
#include"TechUserProxy.hpp"

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


/**
* @brief Default destroyer of SimulatorProxy
*/
SimulatorProxy::~SimulatorProxy() {

}

/**
*@brief Initialization function
*/
void SimulatorProxy::init() {

	simxFinish(-1);

	int userclientID = simxStart((simxChar*)"127.0.0.1", 19997, true, true, 50, 5);  //!< Main connection to V-REP   // wait 5 seconds to connect to vrep
	simxInt syncho = simxSynchronous(userclientID, true);  //Synchronous with client
	SimulatorProxy::clientID = userclientID;
	/*
	simxFinish(-1);                 //! Close any previously unfinished business
	int clientID1 = 0;
	clientID1 = simxStart((simxChar*)"127.0.0.1", 19997, true, true, 5000, 5);  //!< Main connection to V-REP   // wait 5 seconds to connect to vrep

	cout << "ClientID=" << clientID1 << "\n";

	Sleep(1000);
	if (clientID1 != -1)  // if Connection status is OK
	{
		cout << " Connection with V-REP established" << endl;
		simxInt syncho = simxSynchronous(clientID1, true);  //Synchronous with client
		/*
		int sim_status;
		sim_status = simxStartSimulation(clientID1, simx_opmode_oneshot); //start simulation in V-rep 
		cout << "Simulation status: " << sim_status << endl;
		if (sim_status == 1) {

			cout << "Simulation Started ..." << endl;
		}
		else {
			cout << "Simulation Not Started ..." << endl;
		}
	

	}

	else
	{
		cout << " Connection status to VREP: FAILED" << endl;
	}
	simxFinish(clientID1);

	*/

    }


void SimulatorProxy::setSimulatedToolData(double *data) {


	int userclientID = SimulatorProxy::clientID;
		
	//	simxStartSimulation(userclientID, simx_opmode_oneshot); //start simulation in V-rep 

		int polaris_probe = 0;
		simxGetObjectHandle(userclientID, "Shape", &polaris_probe, simx_opmode_oneshot_wait);  // Get Shape(RigidBody)

		//Position  data
		
		double	Rx = data[4] *(-1) ;       //td.transform.Rx
		double	Ry = data[5] * (-1);      //td.transform.Ry
		double	Rz =data[6] * (-1);     //td.transform.Rz

	    	std::cout << "Real Data  :" << data[4] << "\t" << data[5] << "\t" << data[6] << std::endl;
			std::cout << "Data  to Vrep :" << Rx << "\t" << Ry << "\t" << Rz << std::endl;
			const simxFloat my_position[3] = { Rx,Ry,Rz }; //position of Object(Shape) in  X,Y,Z format inside Vrep

			simxSetObjectPosition(userclientID, polaris_probe, -1, my_position, simx_opmode_oneshot_wait);  // Set new Object Position

			

		

		

}


/**
*@brief Verify if the sensor is properly connected to the system and ready for communication (set available flag)
*@return flag stating if the sensor is present
*/
void SimulatorProxy::checkConnection() {


}


/**
*@brief Error Connection Message of the sensor
*@return the message string
*/
char* SimulatorProxy::errorConnectionMessage() {


	return "[SIMULATOR] Simulator not detected. Cannot run the required functionalities.";

}