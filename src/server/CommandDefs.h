/*
 * CommandDefs.h
 *
 *  Created on: 13 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef COMMANDDEFS_H_
#define COMMANDDEFS_H_

#include "common/KeyStore.h"

namespace cryomesh {

/**
 * Keystore of string commands that can be exchanged between client/servers
 */
class CommandDefs : common::KeyStore<std::string, std::string> {
public:
	/**
	 * Default constructor
	 */
	CommandDefs(){}

	/**
	 * Default destructor
	 */
	virtual ~CommandDefs(){}
};

}

}

#endif /* COMMANDDEFS_H_ */
