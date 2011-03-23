/*
 * Client.h
 *
 *  Created on: 19 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef CLIENT_H_
#define CLIENT_H_

namespace cryomesh {
namespace server {

/**
 * Client class to interact with the server to manage cryomesh instances
 */
class Client {
public:
	Client();
	virtual ~Client();
};

}
}
#endif /* CLIENT_H_ */
