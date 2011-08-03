/*
 * ConnectionHandler.cpp
 *
 *  Created on: 19 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#include "ConnectionHandler.h"
#include <iostream>

namespace cryomesh {
namespace server {

ConnectionHandler::ConnectionHandler(boost::asio::io_service& io_serv) :
	io_service(io_serv), socket(io_service) {
}

ConnectionHandler::~ConnectionHandler() {
}

void ConnectionHandler::run() {
	try {
		std::cout << "ConnectionHandler::run: " << "DEBUG: Do stuff here" << std::endl;
		std::string message = "Socket debug reply";
		// read data from socket until empty line
		//boost::array<char, 128> buf;
		boost::system::error_code error;
		//size_t lenin = socket.read_some(boost::asio::buffer(buf), error);
		boost::asio::write(socket, boost::asio::buffer(message));

		/*std::cout << "Server::handleAccept: " << "" << std::endl;
		 boost::array<char, 128> buf;
		 boost::system::error_code error;
		 size_t lenin = socket.read_some(boost::asio::buffer(buf), error);
		 std::string bufout = "server replies\n";
		 boost::asio::write(socket, boost::asio::buffer(bufout));
		 if (error == boost::asio::error::eof)
		 return; // Connection closed cleanly by peer.
		 else if (error) {
		 std::cout << "Server::run: " << "ERROR: Communicating with server..." << std::endl;
		 throw boost::system::system_error(error); // Some other error.
		 }
		 std::cout << "Server::run: " << "SERVER: recv: " << buf.data() << " " << lenin << std::endl;
		 std::cout.write(buf.data(), lenin);
		 */
		socket.close();
		// reset pointer to themself, destroying current object
		shared_from_this().reset();

	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

}//NAMESPACE
}//NAMESPACE
