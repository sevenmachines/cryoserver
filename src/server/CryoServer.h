/*
 * CryoServer.h
 *
 *  Created on: 13 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef CRYOSERVER_H_
#define CRYOSERVER_H_

namespace cryomesh {

namespace server {

/**
 * Server will have responsibility for
 * - control cryomesh managers
 * - organise database storage for generated cryomesh information
 * - update cryomesh's source of reference database information
 * - Act as a server for clients to pass control messages to cryomesh instances
 */
class CryoServer {
public:
	CryoServer();
	virtual ~CryoServer();
};

}

}

#endif /* CRYOSERVER_H_ */
