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
#include "ConnectionHandler.h"

#include <list>
#include <map>
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include <ostream>
#include <boost/asio.hpp>

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
	enum ServerType {
		SYNC, ASYNC
	};
	Server(const ServerType type = SYNC);
	virtual ~Server();
	void run();
	void doJobs(JobPriority priority);
	void addJob(CommandList com, JobPriority priority);

	const std::list<boost::shared_ptr<Job> > & getImmediateJobs() const;

	const std::list<boost::shared_ptr<Job> > & getCycleJobs() const;

	const std::list<boost::shared_ptr<Job> > & getCasualJobs() const;

	/**
	 * To stream operator
	 *
	 *	@param std::ostream & os
	 *		The output stream
	 *	@param const Server & obj
	 *		The object to stream
	 *
	 *	@return std::ostream &
	 *		The output stream
	 */
	friend std::ostream& operator<<(std::ostream & os, const Server & obj);

	static commandFunction RUN_COMMAND;
	static commandFunction PAUSE_COMMAND;
	static commandFunction STOP_COMMAND;
	static commandFunction DESTROY_COMMAND;

	static unsigned int HANDLER_COUNT;
	static const int DEFAULT_SERVER_PORT;

protected:

	void runSync();
	void runAsync();
	void processJobs();
	void handleAsyncAccept(const boost::system::error_code& e);
	void handleSyncAccept(boost::asio::ip::tcp::tcp::socket & socket);
	bool parseCommand(const std::string comstr);

	std::list<boost::shared_ptr<Job> > & getMutableJobsList(const JobPriority priority);

	void initialiseManager();

	void initialiseHandlers();

private:
	/**
	 * List of immediate jobs
	 *
	 * @var std::list<boost::shared_ptr< Job > >
	 */
	std::list<boost::shared_ptr<Job> > immediateJobs;

	/**
	 * List of per cycle jobs
	 *
	 * @var std::list<boost::shared_ptr< Job > >
	 */
	std::list<boost::shared_ptr<Job> > cycleJobs;

	/**
	 * List of casual jobs
	 *
	 * @var std::list<boost::shared_ptr< Job > >
	 */
	std::list<boost::shared_ptr<Job> > casualJobs;

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
	boost::shared_ptr<cryomesh::manager::CryoManager> cryomanager;

	/**
	 * Pool of connection handlers waiting to deal with connections
	 *
	 */
	std::vector<boost::shared_ptr<ConnectionHandler> > handlers;

	boost::asio::io_service io_service;

	ServerType serverType;

	boost::asio::ip::tcp::tcp::acceptor acceptor;

	boost::shared_ptr<ConnectionHandler> new_connection; /**< pointer to connection, that will proceed next */

	CommandDefs commandDefs;

};

}
}
#endif /* SERVER_H_ */
