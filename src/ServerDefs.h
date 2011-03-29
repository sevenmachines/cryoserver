/*
 * CommandDefs.h
 *
 *  Created on: 13 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef SERVERDEFS_H_
#define SERVERDEFS_H_

#include "common/KeyStore.h"
#include <string>
#include <boost/shared_ptr.hpp>
#include "manager/CryoManager.h"

namespace cryomesh {

namespace server {

/**
 * Typedef to simplify function pointers to crymesh commands
 */
typedef void (cryomesh::manager::CryoManager::*commandFunction)();

enum JobPriority {
	IMMEDIATE, CYCLE, CASUAL
};

enum CommandList {
	PAUSE, RUN, STOP, DESTROY, NULL_COMMAND
};

/**
 * Keystore of string commands that can be exchanged between client/servers
 */
class CommandDefs: std::map<std::string, CommandList> {
public:
	/**
	 * Default constructor
	 */
	CommandDefs() {
		this->insert(std::pair<std::string, CommandList>("run", RUN));
		this->insert(std::pair<std::string, CommandList>("stop", STOP));
		this->insert(std::pair<std::string, CommandList>("destroy", DESTROY));
		this->insert(std::pair<std::string, CommandList>("pause", PAUSE));
	}
	/**
	 * Default destructor
	 */
	virtual ~CommandDefs() {
	}

	CommandList getCommand(const std::string comstr) const {
		std::map<std::string, CommandList>::const_iterator it_found = this->find(comstr);
		if (it_found == this->end()) {
			return NULL_COMMAND;
		}
		return it_found->second;
	}
protected:

private:
};

}//NAMESPACE
}//NAMESPACE

#endif /* SERVERDEFS_H_ */
