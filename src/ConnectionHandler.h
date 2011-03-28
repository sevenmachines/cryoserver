/*
 * ConnectionHandler.h
 *
 *  Created on: 19 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef CONNECTIONHANDLER_H_
#define CONNECTIONHANDLER_H_

#include <string>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
namespace cryomesh {
namespace server {

/**
 * Server class to handle incoming connections and queue them for execution
 */
class ConnectionHandler: public boost::enable_shared_from_this<ConnectionHandler> {
public:
	ConnectionHandler();
	virtual ~ConnectionHandler();

	/**
	 * Create new connection
	 *
	 * @param io_service io_service in which this connection will work
	 *
	 * @return pointer to newly allocated object
	 */
	static boost::shared_ptr<ConnectionHandler> create(boost::asio::io_service & io_serv) {
		return boost::shared_ptr<ConnectionHandler>(new ConnectionHandler(io_serv));
	}

	/**
	 * Return socket, associated with this connection. This socket used in accept operation
	 *
	 *
	 * @return reference to socket
	 */
	boost::asio::ip::tcp::socket& getSocket() {
		return socket;
	}
	void run();

private:
	ConnectionHandler(boost::asio::io_service & io_serv);

	boost::asio::io_service& io_service; /**< reference to io_service, in which work this connection */
	boost::asio::ip::tcp::socket socket; /**< socket, associated with browser */
	boost::asio::streambuf buf; /**< buffer for request data */
};

}
}
#endif /* CONNECTIONHANDLER_H_ */
