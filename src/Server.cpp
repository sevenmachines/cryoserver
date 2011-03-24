/*
 * Server.cpp
 *
 *  Created on: 19 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#include "Server.h"

using namespace cryomesh::manager;

namespace cryomesh {
namespace server {

commandFunction Server::RUN_COMMAND = &CryoManager::run;
commandFunction Server::PAUSE_COMMAND = &CryoManager::pause;
commandFunction Server::STOP_COMMAND = &CryoManager::stop;
commandFunction Server::DESTROY_COMMAND = &CryoManager::destroy;

Server::Server() {
	initialiseManager();
}

Server::~Server() {
}
void Server::doJobs(JobPriority priority) {
	std::list < boost::shared_ptr<Job> > &jobslist = this->getMutableJobsList(priority);

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
}//NAMESPACE
}//NAMESPACE
