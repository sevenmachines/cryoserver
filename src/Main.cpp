/*
 * Main.cpp
 *
 *  Created on: 19 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#include "Main.h"
#include "Server.h"
#include "ServerDefs.h"

using namespace cryomesh::server;
namespace cryomesh {

Main::Main() {
	// TODO Auto-generated constructor stub

}

Main::~Main() {
	// TODO Auto-generated destructor stub
}

}//NAMESPACE

#ifndef CRYOSERVER_CUTE

int main(int argc, char **argv) {
	std::cout<<"main: "<<"argc: "<<argc;
	std::cout<<"[ ";
	for (int i=0; i<argc; i++){
		std::cout << argv[i];
		if ( i < (argc-1) ){
			std::cout<<", ";
		}
	}
	std::cout << " ]"	<<std::endl;
	Server server;
	server.run();
	//server.addJob(RUN, IMMEDIATE);
//	server.addJob(STOP, CYCLE);
	//std::cout << server << std::endl;

	///TODO maintenace command
//	server.doJobs(IMMEDIATE);
	//server.doJobs(CYCLE);

	//std::cout << server << std::endl;
	return 0;
}

#endif
