/*
 * Server.h
 *
 *  Created on: 19 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef SERVER_H_
#define SERVER_H_

/**
 * Class to collect commands from a ConnectionHandler and to execute those commands
 * at sane points in the running cryomesh process. Commands are grouped into 'immediate',
 * that can be executed at and point in the cycle, and 'cycle' that require the running cryomesh
 * to be in a certain state to be run, ie, the cryomesh is in-between cycles, paused, not initialised,
 * etc. The server also holds the cryomesh manager
 */
namespace cryomesh {

class Server {
public:
	Server();
	virtual ~Server();
};

}

#endif /* SERVER_H_ */
