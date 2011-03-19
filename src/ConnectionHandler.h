/*
 * ConnectionHandler.h
 *
 *  Created on: 19 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef CONNECTIONHANDLER_H_
#define CONNECTIONHANDLER_H_

namespace cryomesh {

/**
 * Server class to handle incoming connections and queue them for execution
 */
class ConnectionHandler {
public:
	ConnectionHandler();
	virtual ~ConnectionHandler();
};

}

#endif /* CONNECTIONHANDLER_H_ */
