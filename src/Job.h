/*
 * Job.h
 *
 *  Created on: 23 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef JOB_H_
#define JOB_H_

namespace cryomesh {

namespace server {

/**
 * Class representing a job for the server to carry out
 */
class Job {
public:
	Job();
	virtual ~Job();
};

}

}

#endif /* JOB_H_ */
