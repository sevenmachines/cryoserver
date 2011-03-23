/*
 * Server.h
 *
 *  Created on: 19 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "Job.h"
#include "manager/CryoManager.h"

#include <list>
#include <map>
#include <string>
/**
 * Class to collect commands from a ConnectionHandler and to execute those commands
 * at sane points in the running cryomesh process. Commands are grouped into 'immediate',
 * that can be executed at and point in the cycle, and 'cycle' that require the running cryomesh
 * to be in a certain state to be run, ie, the cryomesh is in-between cycles, paused, not initialised,
 * etc. The server also holds the cryomesh manager
 */
namespace cryomesh {
namespace server {

class Server {
public:

	/**
	 * Typedef to simplify function pointers to crymesh commands
	 */
	typedef void (cryomesh::manager::CryoManager::*commandFunction)	();

	Server();
	virtual ~Server();

private:
	/**
	 * List of immediate jobs
	 *
	 * @var std::list<Job>
	 */
	std::list<Job> immediateJobs;

	/**
	 * List of per cycle jobs
	 *
	 * @var std::list<Job>
	 */
	std::list<Job> cycleJobs;

	/**
	 * List of maintenance jobs
	 *
	 * @var std::list<Job>
	 */
	std::list<Job> maintenceJobs;

	/**
	 * Mapping of string commands to function pointer commands
	 *
	 *	@var std::map<std::string, commandFunction>
	 */
	std::map<std::string, commandFunction> serverCommandFunctions;
};

}
}
#endif /* SERVER_H_ */
