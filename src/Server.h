/*
 * Server.h
 *
 *  Created on: 19 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "Job.h"
#include "ServerDefs.h"
#include "manager/CryoManager.h"
#include "common/SimpleCollection.h"

#include <list>
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>

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

	Server();
	virtual ~Server();
	void doJobs(JobPriority & priority);
	void addJob(CommandList com, JobPriority & priority);

protected:
	std::list<boost::shared_ptr< Job > > & getMutableJobsList(const JobPriority & priority);

private:
	/**
	 * List of immediate jobs
	 *
	 * @var std::list<boost::shared_ptr< Job > >
	 */
	std::list<boost::shared_ptr< Job > > immediateJobs;

	/**
	 * List of per cycle jobs
	 *
	 * @var std::list<boost::shared_ptr< Job > >
	 */
	std::list<boost::shared_ptr< Job > > cycleJobs;

	/**
	 * List of maintenance jobs
	 *
	 * @var std::list<boost::shared_ptr< Job > >
	 */
	std::list<boost::shared_ptr< Job > > maintenceJobs;

	/**
	 * Mapping of string commands to function pointer commands
	 *
	 *	@var std::map<CommandList, commandFunction>
	 */
	std::map<CommandList, commandFunction> serverCommandFunctions;

	/**
	 * The cryomanager associated with this server
	 *
	 * @var boost::shared_ptr< manager::CryoManager >
	 */
	boost::shared_ptr< cryomesh::manager::CryoManager > cryomanager;
};

}
}
#endif /* SERVER_H_ */
