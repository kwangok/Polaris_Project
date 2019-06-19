#include "SimulatorProxy.hpp"






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

#define KEY_ESCAPE 27   //Exit 

// Arrow Key  --- Position
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
// Orientation Key
#define KEY_W 87   //w
#define KEY_A 65  //s
#define KEY_D 68 //a

extern "C" {
#include "extApi.h"
}



/**
* @brief Default constructor of SimulatorProxy
*/
SimulatorProxy::SimulatorProxy(){

	this->connected = false;





		int polaris_probe = 0;

		//Load Scence of Vrep
		//  path = 'C:\Users\AHMAD\Downloads\My_Sample\Testing\vrepTest\Polaris_test.ttt';
		int return_v;

		system("start Polaris_test_Shortcut "); //for open vrep scence by its shortcut 

												//"continuous remote API server service"
												// Remember that v_repExtRemoteApi.dll plugin for V-rep's side loaded on startup
												//Check also remoteApiConnections.txt file for port configuration

		simxFinish(-1);                 //! Close any previously unfinished business
		int clientID = 0;
		Sleep(5000);
		clientID = simxStart((simxChar*)"127.0.0.1", 19997, true, true, 5000, 5);  //!< Main connection to V-REP
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
			simxGetObjectHandle(clientID, "Shape", &polaris_probe, simx_opmode_oneshot_wait);  // Get Shape(RigidBody)
			cout << "Use Arrow Keys to move the Object." << endl;
			cout << " \nPress x to stop simulation the program . . ." << endl;
			cout << "\n \n \nPress ESC to Exit the program . . ." << endl;
			// Recieve commands from Keyboard Arrow Keys
			int c = 0;
			float x, y;  //X ,Y position

			x = 0.5;
			y = 0.5;

			while (1)
			{
				const simxFloat my_position[3] = { x,y,1.0 }; //position of Object(Shape) in  X,Y,Z format

				switch (c = _getch()) {

				case KEY_ESCAPE:
					system("taskkill /F /T /IM vrep.exe"); //Exit the V-rep Environment
					

					break;
				case 'x':  //stop simulation key
					simxStopSimulation(clientID, simx_opmode_oneshot_wait); //stop simulation in V-rep 
					cout << "Simulation Stoped ..." << endl;
					break;


				case KEY_UP:
					// key up
					x += 0.0;
					y += 0.2;
					break;

				case KEY_DOWN:
					// key down
					x += 0.0;
					y += -0.2;

					break;

				case KEY_LEFT:
					// key left
					x += 0.2;
					y += 0.0;

					break;
				case KEY_RIGHT:
					// key left
					x += -0.2;
					y += 0.0;
					break;

				default:
					// not arrow
					x += 0.0;
					y += 0.0;
					break;
				}

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