## Polaris_Project (Under Development)


 <p align="center">
  <img width="260" height="200"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris_Vicra.jpg">
</p>

This is a project based on Polaris Vicra sensor and has been written in C++ Language and project folder's name is "alba".

3D Mechanical part of Rigid Body has been designed in FreeCad Design software.

The Simulation environment is V-REP and APIs has been developed in VS2015.

<br>
 <p align="center">
  <img width="100" height="100"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Freecad.jpg">
  <img width="130" height="100" style="margin-left=10px;" src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/vrep_logo.png">
  <img width="150" height="100" style="margin-left=20px;" src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/vs2015.png">
</p>

below you can see photos of the Designed mechanical part in FreeCad :
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
Import to V-Rep enviornment as .obj file.
<br> 
<p align="center">
  <img width="350" height="230"  src="https://github.com/ahmadkh1995/Polaris_Project/blob/master/Polaris%203D/Polaris_8.png">
</p>


-------------------------------------------------------------------------------------------------------------------
// Recieve Position Data from Polaris sensor

---
The API Commnads which should be initialized till framework starts to recieve position data

First check flowchart in page-26

1---> "INIT" ----> Initializes the system.

2--->"PHSR" ---->Returns the number of assigned port handles and the port status for each one. Assigns a port handle
to a wired tool, GPIO device, or strober

3--->"PHINF"--->Returns port handle status, information about the tool associated with the port handle, and the
physical location of a port handle.

4---> "PHRQ" ---->Assigns a port handle to a tool or GPIO device.

5--->"PVWR" ----> Assigns a tool definition file to a wireless tool, or overrides the SROM device in a wired tool or GPIO device.

6---> "PINIT" ----> Initializes a port handle

7--->"PENA"--->Enables the reporting of transformations for a particular port handle.

8---> Load the Tool(.srom file)

//Here we have 3 options:

8a --->"3D" ---->Returns the latest three-dimensional marker position of a single marker or multiple markers.
8b --->"BX" ---->Returns the latest tool transformations, individual marker positions, and system status in binary format.
8c --->"TX" ---->Returns the latest tool transformations, individual marker positions, and system status in text format.

note:  a port handle must be initialized (PINIT) before it can be enabled (PENA).

-Commands must be sent from the host computer to the system in one of the two following formats. 
<Command><SPACE><Parameter1><Parameter2>...<ParameterN><CR>

 If a complete command is received by the system, replies are sent back in the format:
<Reply><CRC16>
----------------------------------------------------------------------------------------------
These functions located in CombinedApi.cpp file

1. INIT ---->  CombinedApi::initialize()
2.PHSR ----> CombinedApi::portHandleSearchRequest()
3.PHINF ---->CombinedApi::portHandleInfo()
3a.PHF ----> portHandleFree()
4.PHRQ ---->CombinedApi::portHandleRequest()
5.PINIT----> CombinedApi::portHandleInitialize()
6.PENA---->CombinedApi::portHandleEnable()
7.PVWR---->CombinedApi::loadSromToPort()
8. Start to Track  ---->startTracking()
9.Stop Tracking ---->stopTracking()
10.Get Data (TX) ---->getTrackingDataTX()
11.Get Data (BX) ---->getTrackingDataBX()
12.Get Data (BX2) ---->getTrackingDataBX2()
13. Get Errors or warning messages -----> getErrorString() ----------  getWarningString()  -------getErrorCodeFromResponse()
14.Reads the response from the device ----> readResponse() 

-note that for processing the errors/warnings or reply we could use this convertion functions:
A) string intToString()    B) stringToInt()    C) errorToString()

---------------------------------------------------------------------------------------------
These functions located in MarkerData.cpp file
-Marker status---->MarkerStatus() ---->"OK , MissingOutOfVolume ,Saturated ,..."
-markerIndex
-The marker position (x,y,z) [mm] ---->double x,y,z

---------------------------------------------------------------------------------------------
These functions are in portHandleInfo.cpp

Returns the port handle as a string---->getPortHandle()
Returns the tool's revision number---->getRevision()
Return the status as a string ----> getStatus() 
---------------------------------------------------------------------------------------------
These functions are in GbfData3D.cpp
"This class encapsulates 3D marker data as it is read from BX2"

GbfData3D::GbfData3D(BufferedReader& reader,  int numberOfTools)

-Read the data--->toolHandle = reader.get_uint16(); 		numberOf3Ds = reader.get_uint16();

Put the toolHandle into its own vector ---->toolHandles.push_back(toolHandle);

Create a corresponding vector with the 3Ds -----> std::vector<MarkerData> list3Ds;

pos.x = reader.get_double();
pos.y = reader.get_double();
pos.z = reader.get_double();
----------------------------------------------------------------------------------------------








