#ifndef USERPROXY_HPP_
#define USERPROXY_HPP_

// Project Header files
#include "UserProxyInterface.hpp"
#include "utils.hpp"

// Action type defines
#define PAIRING 1
#define REGISTRATION 2
#define POSITIONING 3
#define QUIT_INPUT 0

class UserProxy : public UserProxyInterface {

public:

	/**
	* @brief Default constructor of UserProxy
	*/
	UserProxy();

	/**
	* @brief Default destroyer of UserProxy
	*/
	~UserProxy();

	/**
	* @brief Get the user type
	*/
	inline int getUserType() { return userType; }

	/**
	* @brief Allow selection of the action for the user
	* @param the code of the chosen option
	* @param the set of input arguments passed to the program
	* @return forward the code of the chosen option
	*/
	int sendRequest(const int& req, const char** argv);

	/**
	* @brief Method that forwards the request to start the Pairing procedure
	*/
	bool requestForPairing();

	/**
	* @brief Method that forwards the request to start the Registration procedure
	* @param the set of input arguments passed to the program
	*/
	bool requestForRegistration(const char** argv);

	/**
	* @brief Method that forwards the request to start the Computer-Assisted Positioning procedure
	*/
	bool requestForComputerAssistedPositioning();

	/**
	* @brief Check if the user is a technician
	*/
	inline bool isATechUser(){ return false; }

protected:

	int userType;				//!< Type of the user (Generic or Technician)

	/**
	* @brief Check the validity of the option chosen by the user in the Menu
	* @param the code of the chosen option
	* @return a flag indicating the validity
	*/
	bool checkOptionValidity(const int& op);



};

#endif //USERPROXY_HPP_