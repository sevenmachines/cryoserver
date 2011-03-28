/*
 * Server.cpp
 *
 *  Created on: 19 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#include "Server.h"
#include "ConnectionHandler.h"
#include <boost/bind.hpp>
#include <boost/thread.hpp>

using namespace cryomesh::manager;
using boost::asio::ip::tcp;

namespace cryomesh {
namespace server {

commandFunction Server::RUN_COMMAND = &CryoManager::run;
commandFunction Server::PAUSE_COMMAND = &CryoManager::pause;
commandFunction Server::STOP_COMMAND = &CryoManager::stop;
commandFunction Server::DESTROY_COMMAND = &CryoManager::destroy;
const int Server::DEFAULT_SERVER_PORT = 10666;
unsigned int Server::HANDLER_COUNT = 1;

Server::Server(const ServerType type) :
	acceptor(io_service, tcp::endpoint(tcp::v4(), DEFAULT_SERVER_PORT)) {
	if (serverType == ASYNC) {
		new_connection = ConnectionHandler::create(io_service);
		initialiseManager();
	}
}

Server::~Server() {
}

void Server::handleAsyncAccept(const boost::system::error_code& e) {
	std::cout << "Server::handleAccept: " << "" << std::endl;
	if (!e) {

		// run connection in new thread
		boost::thread thr(boost::bind(&ConnectionHandler::run, new_connection));

		// create next connection, that will accepted
		new_connection = ConnectionHandler::create(io_service);
		// start new accept operation
		acceptor.async_accept(new_connection->getSocket(),
				boost::bind(&Server::handleAsyncAccept, this, boost::asio::placeholders::error));

	}

}

void Server::handleSyncAccept(tcp::socket & socket) {
	boost::array<char, 128> buf;
	boost::system::error_code error;
	size_t lenin = socket.read_some(boost::asio::buffer(buf), error);
	boost::asio::write(socket, boost::asio::buffer("ballsamento!"));
	std::cout<<"Server::handleSyncAccept: "<<buf.data()<<std::endl;
	socket.close();
}

void Server::processJobs() {
	bool have_connection = false;
	bool have_immediate_jobs = false;
	bool have_cycle_jobs = false;

	//std::cout << "Server::run: " << "DEBUG: Starting to process jobs..." << std::endl;
	have_immediate_jobs = immediateJobs.size() > 0;
	if (have_immediate_jobs == true) {
		std::cout << "Server::run: " << "DEBUG: Processing immediate jobs..." << std::endl;
		// need to stop run thread
		//handle requests
	}

	have_cycle_jobs = cycleJobs.size() > 0;
	if (have_cycle_jobs == true) {
		std::cout << "Server::run: " << "DEBUG: Processing cycle jobs..." << std::endl;
		// wait to stop run thread
		//handle requests
	}
}

void Server::run() {
	std::cout<<"Server::run: "<<""<<std::endl;
	if (serverType == SYNC) {
		this->runSync();
	} else if (serverType == ASYNC) {
		this->runAsync();
	}
}

void Server::runSync() {
	std::cout<<"Server::runSync: "<<""<<std::endl;
	for (;;) {
		tcp::socket socket(io_service);
		acceptor.accept(socket);
		this->handleSyncAccept(socket);
	}
}
void Server::runAsync() {
	std::cout<<"Server::runAsync: "<<""<<std::endl;
	bool quit_server = false;
	while (quit_server == false) {
		try {

		} catch (std::exception& e) {
			std::cout << "Server::run: " << "ERROR: Trying to connect to server..." << std::endl;
			std::cerr << e.what() << std::endl;
		}

		std::cout << "Server::run: " << "DEBUG: Server stopping..." << std::endl;
	}
}

void Server::doJobs(JobPriority priority) {
	std::list<boost::shared_ptr<Job> > &jobslist = this->getMutableJobsList(priority);

	while (jobslist.size() > 0) {
		commandFunction func = jobslist.front()->getFunction();
		//std::cout<<count<<": "<<it_map->first<<std::endl;
		((*cryomanager).*func)();
		jobslist.pop_front();
	}

}

void Server::addJob(CommandList com, JobPriority priority) {
	boost::shared_ptr<Job> tempjob;
	commandFunction tempfunc;
	/*
	 if (com == RUN) {
	 tempfunc = RUN_COMMAND;
	 } else if (com == PAUSE) {
	 tempfunc = PAUSE_COMMAND;
	 } else if (com == STOP) {
	 tempfunc = STOP_COMMAND;
	 }else if (com == DESTROY) {
	 tempfunc = DESTROY_COMMAND;
	 }

	 tempjob = boost::shared_ptr<Job>(new Job(com, priority, tempfunc));

	 if (priority == IMMEDIATE) {
	 immediateJobs.push_back(tempjob);
	 } else if (priority == CYCLE) {
	 cycleJobs.push_back(tempjob);
	 } else if (priority == CASUAL) {
	 casualJobs.push_back(tempjob);
	 }
	 */
	// TODO - need to fix mapping of function pointers

	std::map<CommandList, commandFunction>::iterator it_found = serverCommandFunctions.find(com);
	if (it_found != serverCommandFunctions.end()) {
		tempfunc = it_found->second;
		tempjob = boost::shared_ptr<Job>(new Job(com, priority, tempfunc));

		if (priority == IMMEDIATE) {
			immediateJobs.push_back(tempjob);
		} else if (priority == CYCLE) {
			cycleJobs.push_back(tempjob);
		} else if (priority == CASUAL) {
			casualJobs.push_back(tempjob);
		}
	} else {
		std::cout << "Server::addJob: " << "WARNING: Job function mapping not found, ignoring..." << std::endl;
	}

}

std::list<boost::shared_ptr<Job> > & Server::getMutableJobsList(const JobPriority priority) {
	if (priority == IMMEDIATE) {
		return immediateJobs;
	} else if (priority == CYCLE) {
		return cycleJobs;
	} else if (priority == CASUAL) {
		return casualJobs;
	}
	std::cout << "Server::getMutableJobsList: " << "WARNING: Jobs list not found, returning maintenance list..."
			<< std::endl;
	return casualJobs;
}

const std::list<boost::shared_ptr<Job> > & Server::getImmediateJobs() const {
	return immediateJobs;
}

const std::list<boost::shared_ptr<Job> > & Server::getCycleJobs() const {
	return cycleJobs;
}

const std::list<boost::shared_ptr<Job> > & Server::getCasualJobs() const {
	return casualJobs;
}

std::ostream& operator<<(std::ostream & os, const Server & obj) {
	int imm_sz = obj.getImmediateJobs().size();
	int cyc_sz = obj.getCycleJobs().size();
	int man_sz = obj.getCasualJobs().size();
	os << "Server: " << "\tjobs:" << imm_sz << "/" << cyc_sz << "/" << man_sz;
	return os;
}

void Server::initialiseManager() {
	cryomanager = boost::shared_ptr<cryomesh::manager::CryoManager>(new cryomesh::manager::CryoManager());
	//serverCommandFunctions.insert(std::pair<std::string, commandFunction>("RUN", &cryomesh::manager::CryoManager::pause));
	serverCommandFunctions[PAUSE] = &cryomesh::manager::CryoManager::pause;
	serverCommandFunctions[RUN] = &cryomesh::manager::CryoManager::run;
	serverCommandFunctions[STOP] = &cryomesh::manager::CryoManager::stop;
	serverCommandFunctions[DESTROY] = &cryomesh::manager::CryoManager::destroy;
}

//TODO
void Server::initialiseHandlers() {
	//for (int i = 0; i< HANDLER_COUNT; i++) {
	//	boost::shared_ptr< ConnectionHandler > temp_handler(new ConnectionHandler (*this));
	//	handlers.push_back(temp_handler) ;
	//}
}
}//NAMESPACE
}//NAMESPACE
