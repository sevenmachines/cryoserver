/*
 * Job.cpp
 *
 *  Created on: 23 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#include "Job.h"

namespace cryomesh {

namespace server {

Job::Job(CommandList com, JobPriority & pty, commandFunction func) :
	command(com), priority(pty), function(func) {

}

Job::~Job() {
}

const CommandList & Job::getCommand() const {
	return command;
}
const JobPriority & Job::getPriority() const {
	return priority;
}
commandFunction Job::getFunction(){
	return function;
}

}//NAMESPACE

}//NAMESPACE
