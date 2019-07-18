## NDI Polaris Sensor Tracker Project 

 <p align="center">
  <img width="260" height="200"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris_Vicra.jpg">
</p>

This is a project based on **NDI Polaris Vega sensor** (Also it can be used for Vicra Sensor) and has been written in C++ Language and project code for this framework is located in the folder "alba".

3D Mechanical part of Rigid Body has been designed in **FreeCad Design software** .

The Simulation environment is **V-REP** and APIs has been developed in **Visual Studio 2015** .

<br>
 <p align="center">
  <img width="100" height="100"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Freecad.jpg">
  <img width="130" height="100" style="margin-left=10px;" src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/vrep_logo.png">
  <img width="150" height="100" style="margin-left=20px;" src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/vs2015.png">
</p>
 <p align="center">
 This system will be used in surgery room to assist surgeon in collaberating with a Robotic system.
  <img width="460" height="340"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Tracker_project.png">
</p>

Goals of this project is :

**I)** Design 3D Mechanical part of the tools(Here we have 3 tools) in FreeCAD  and import them as Object to V-Rep environment.

**II)** Connect VS2015 to V-Rep API and send and receive (Position/Orientation) data to Object in V-rep with keyboard's keys.

**III)** Connect VS2015 to Polaris Vega's API and recieve some data of tool Markers.

**IV)** Visulaize the Polaris Tool in V-rep stimuasly based on Tool's position and data (which is acquiring by Polaris Sensor).


below you can see photos of the Designed mechanical part in FreeCad.
All 3D source files are located in FreeCad folder(.fcstd and .obj).

<p align="center">
  <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Polaris_1.png">
   <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Polaris_2.png">
  <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Polaris_3.png">
  <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Polaris_4.png">
</p>

<p align="center">
  <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Polaris_5.png">
   <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Polaris_6.png">
  <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Polaris_7.png">
</p>
As you can see in photos ,there are 3 tools which designed in FreeCad.


<p align="center">
  <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/FreeCad/Part_2.png">
   <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/FreeCad/Part2_2.png">
  <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/FreeCad/Part2_3.png">
</p>
<p align="center">
  <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/FreeCad/Part3_1.png">
   <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/FreeCad/Part3_2.png">
  <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/FreeCad/Part3_3.png">
</p>
<br> 
Import to V-Rep enviornment as .obj file and attach a dummy.
<br> 
<p align="center">
  <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Dummy1.PNG">
   <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Dummy2.PNG">
   <img width="200" height="150"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Dummy3.PNG">
 </P>
 <br> 
<p align="center">
  <img width="300" height="230"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Dummy1_b.PNG">
  <img width="300" height="230"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Dummy2_b.PNG">

</p>

Framework :

 <p align="center">
  <img  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/ALBA_Project.png">
 <img  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/ALBA (Tracking).png">
</p>



The Polaris Sensor's Low-Level Commnads which should be initialized till framework starts to recieve position data

### Flowchart of the System(with Low-Level Functions)

<p align="center">

  <img width="280" height="500"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/FlowChart.PNG">
</p>




**Description of Some of Low-level functions inside Polaris Sensor **

1) **INIT** -> Initializes the system.

2) **PHSR** -> Returns the number of assigned port handles and the port status for each one. Assigns a port handle
to a wired tool, GPIO device, or strober

3) **PHINF** -> Returns port handle status, information about the tool associated with the port handle, and the
physical location of a port handle.

4) **PHRQ** -> Assigns a port handle to a tool or GPIO device.

5) **PVWR** -> Assigns a tool definition file to a wireless tool, or overrides the SROM device in a wired tool or GPIO device.

6) **PINIT** -> Initializes a port handle

7) **PENA** -> Enables the reporting of transformations for a particular port handle.

8) Load the Tool (**.srom file**)

//Here we have 3 options:

8a) **3D** -> Returns the latest three-dimensional marker position of a single marker or multiple markers.

8b) **BX** -> Returns the latest tool transformations, individual marker positions, and system status in binary format.

8c) **TX** -> Returns the latest tool transformations, individual marker positions, and system status in text format.

**note:  a port handle must be initialized (PINIT) before it can be enabled (PENA).**
  
### Description of Some of main C++ functions in Polaris API **
**These files are not included in the Project folder **

These functions located in **CombinedApi.cpp** file.

    1)INIT ---->  CombinedApi::initialize()

    2)PHSR ----> CombinedApi::portHandleSearchRequest()

    3.PHINF ---->CombinedApi::portHandleInfo()

    3a.PHF ----> portHandleFree()

    4.PHRQ ---->CombinedApi::portHandleRequest()

    5.PINIT----> CombinedApi::portHandleInitialize()

    6.PENA---->CombinedApi::portHandleEnable()

    7.PVWR---->CombinedApi::loadSromToPort()

    8.Start to Track  ---->startTracking()

    9.Stop Tracking ---->stopTracking()

    10.Get Data (TX) ---->getTrackingDataTX()

    11.Get Data (BX) ---->getTrackingDataBX()

    12.Get Data (BX2) ---->getTrackingDataBX2()

    13.Get Errors or warning messages:

     getErrorString()
     getWarningString() 
     getErrorCodeFromResponse()

    14.Reads the response from the device ----> readResponse() .

    note that for processing the errors/warnings or reply we could use this convertion functions:

    A) string intToString() 

    B) stringToInt() 

    C) errorToString()


These functions located in **MarkerData.cpp** file

    -Marker status---->MarkerStatus() ---->"OK , MissingOutOfVolume ,Saturated ,..."

    -markerIndex

    -The marker position (x,y,z) [mm] ---->double x,y,z

These functions are in **portHandleInfo.cpp**

    Returns the port handle as a string---->getPortHandle()

    Returns the tool's revision number---->getRevision()

    Return the status as a string ----> getStatus() 

These functions are in **GbfData3D.cpp**  (For this project I didn't use the class)

**This class encapsulates 3D marker data as it is read from BX2**

    GbfData3D::GbfData3D(BufferedReader& reader,  int numberOfTools)

    -Read the data--->toolHandle = reader.get_uint16(); 
    numberOf3Ds = reader.get_uint16();

    Put the toolHandle into its own vector ---->toolHandles.push_back(toolHandle);

    Create a corresponding vector with the 3Ds -----> std::vector<MarkerData> list3Ds;

    pos.x = reader.get_double();

    pos.y = reader.get_double();

    pos.z = reader.get_double();

### V-Rep API Codes:
**Notes:** For Connecting the project to V-Rep we should add following directories to the "Additional Include Directories" inside the Visual Studio 2015:

         C:\Program Files\V-REP3\V-REP_PRO_EDU\programming\remoteApi

         C:\Program Files\V-REP3\V-REP_PRO_EDU\programming\include

also we should add theses lines to preprocessor definition in Project properties section:
(because extApi might get parsed/compiled before your file where you have the definition)

          -   NON_MATLAB_PARSING
          -   DO_NOT_USE_SHARED_MEMORY
          -   MAX_EXT_API_CONNECTIONS=255
          _   CRT_SECURE_NO_WARNINGS

more details: http://www.coppeliarobotics.com/helpFiles/en/remoteApiClientSide.htm


These codes are located in **PolarisProxy.cpp** file.


    #include "SimulatorProxy.hpp"
    #include"TechUserProxy.hpp"

    #include <conio.h>
    #include "windows.h"
    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    using namespace std;
    
    extern "C" {
    #include "extApi.h"
     }

    void SimulatorProxy::init() {
	   
    simxFinish(-1);  //Finish all previous tasks
    
     int userclientID = simxStart((simxChar*)"127.0.0.1", 19997, true, true, 50, 5);  //!< Main connection to V-REP // wait 5    seconds to connect to vrep
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
		
	//simxStartSimulation(userclientID, simx_opmode_oneshot); //start simulation in V-rep 

	int polaris_probe = 0;
	simxGetObjectHandle(userclientID, "Dummy", &polaris_probe, simx_opmode_oneshot_wait);  // Get Shape(RigidBody)

	int polaris_sensor = 0;
	simxGetObjectHandle(userclientID, "Dummy0", &polaris_sensor, simx_opmode_oneshot_wait);  // Get Shape(RigidBody)

	//Position(X,Y,Z format)  data
	double	tx = data[0]/1000 ;       //td.transform.tx
	double	ty = data[1] /1000;      //td.transform.ty
	double	tz = data[2] /1000;     //td.transform.tz

	//Orientation (Quaternion format)  data
	double	Q0 = data[3] ;     //td.transform.q0
	double	Qx = data[4] ;       //td.transform.qx
	double	Qy = data[5] ;      //td.transform.qy
	double	Qz =data[6] ;     //td.transform.qz

	std::cout << "Position Data  :" << "X: "<< tx << "\t" << "Y: " <<ty << "\t" << "Z: " << tz << std::endl;

	std::cout << "Orientation Data  :" << "q0: " <<Q0 << "\t" << "qx: " << Qx << "\t" << "qy: " << Qy << "\t" << "qz: " << Qz   << std::endl;

	const simxFloat my_position[3] = { tx,ty,tz }; // position of Object(Shape) in  X,Y,Z format 

	const simxFloat my_orientation[4]= {Qx,Qy,Qz,Q0 }; // orientation of Object(Shape) in  {qx,qy,qz,w} "Quaternion " format

	simxSetObjectPosition(userclientID, polaris_probe, polaris_sensor, my_position, simx_opmode_oneshot_wait);  // Set new Object Position

	simxSetObjectQuaternion(userclientID, polaris_probe, polaris_sensor, my_orientation, simx_opmode_oneshot_wait);  // Set new Object Position

  }








