/*
 * Job.h
 *
 *  Created on: 23 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef JOB_H_
#define JOB_H_

#include "ServerDefs.h"

namespace cryomesh {

namespace server {

/**
 * Class representing a job for the server to carry out
 */
class Job {
public:

	Job(CommandList com, JobPriority & pty, commandFunction  func);
	virtual ~Job();

	const CommandList & getCommand() const;
	const JobPriority & getPriority()const;
	commandFunction getFunction();

private:
	CommandList command;
	JobPriority priority;
	commandFunction  function;
};

}

}

#endif /* JOB_H_ */
