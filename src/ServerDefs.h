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
typedef void (cryomesh::manager::CryoManager::*commandFunction)	();

enum JobPriority {
	IMMEDIATE, CYCLE, CASUAL
};

enum CommandList {
	PAUSE, RUN, STOP, DESTROY
};

/**
 * Keystore of string commands that can be exchanged between client/servers
 */
class CommandDefs: common::KeyStore<std::string, CommandList> {
public:

	static const CommandDefs & getSingleton() {
		if (defs == 0) {
			defs = boost::shared_ptr<CommandDefs>(new CommandDefs);
		}
		return * defs;
	}
	/**
	 * Default destructor
	 */
	virtual ~CommandDefs() {
	}

protected:
	/**
	 * Default constructor
	 */
	CommandDefs() {
		this->add("run", RUN);
		this->add("stop", STOP);
		this->add("destroy", DESTROY);
		this->add("pause", PAUSE);
	}

private:
	static boost::shared_ptr<CommandDefs> defs;
};

}//NAMESPACE
}//NAMESPACE

#endif /* SERVERDEFS_H_ */
