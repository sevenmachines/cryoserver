/*
 * Server.cpp
 *
 *  Created on: 19 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#include "Server.h"

namespace cryomesh {
namespace server {

Server::Server() {
	cryomanager = boost::shared_ptr< cryomesh::manager::CryoManager > (new cryomesh::manager::CryoManager());
}

Server::~Server() {
}
void Server::doJobs(JobPriority & priority) {
	std::list<boost::shared_ptr<Job> > & jobslist = this->getMutableJobsList(priority);

	while (jobslist.size() > 0) {
		commandFunction func = jobslist.front()->getFunction();
		//std::cout<<count<<": "<<it_map->first<<std::endl;
		((*cryomanager).*func)();
		jobslist.pop_front();
	}

}

void Server::addJob(CommandList com, JobPriority & priority) {
	std::map<CommandList, commandFunction>::iterator it_found = serverCommandFunctions.find(com);
	if (it_found != serverCommandFunctions.end()) {
		commandFunction tempfunc = it_found->second;
		boost::shared_ptr<Job> tempjob(new Job(com, priority, tempfunc));

		if (priority == IMMEDIATE) {
			immediateJobs.push_back(tempjob);
		} else if (priority == CYCLE) {
			cycleJobs.push_back(tempjob);
		} else if (priority == MAINTENANCE) {
			maintenceJobs.push_back(tempjob);
		}
	} else {
		std::cout << "Server::addJob: " << "WARNING: Job function mapping not found, ignoring..." << std::endl;
	}
}

std::list<boost::shared_ptr<Job> > & Server::getMutableJobsList(const JobPriority & priority) {
	if (priority == IMMEDIATE) {
		return immediateJobs;
	} else if (priority == CYCLE) {
		return cycleJobs;
	} else if (priority == MAINTENANCE) {
		return maintenceJobs;
	}
	std::cout << "Server::getMutableJobsList: " << "WARNING: Jobs list not found, returning maintenance list..." << std::endl;
	return maintenceJobs;
}

}//NAMESPACE
}//NAMESPACE
