#pragma once
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <string> 
#include <vector>
#include <algorithm>
#include <stdio.h>
#include "./execShell.hpp"

using boost::asio::ip::tcp;

using namespace std;
#define DEFAULT_PORT 12345
#define VERSION "Telnet demon version 0.0.0.1.a"
class session
{
	public:
  		session(boost::asio::io_service& io_service): socket_(io_service){memset(data_, 0,max_length);};
  		tcp::socket& socket();
  		void start();
		void setParam(unsigned short port, unsigned int time_out, vector<string> allowedCommands);
	private:
  		void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
  		void handle_write(const boost::system::error_code& error);
  		tcp::socket socket_;
  		enum { max_length = 65536 };
  		char data_[max_length];
		unsigned short port;
		unsigned int time_out;
		vector<string> allowedCommands;
};

class TelnetServer
{
	public:
  		TelnetServer(boost::asio::io_service& io_service, unsigned short port, unsigned int time_out, vector<string> allowedCommands)
    		: io_service_(io_service),acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
  		{
			this->port = port;
			this->time_out = time_out;
			this->allowedCommands = allowedCommands;
    			start_accept();
  		}
		void setAllowedCommands(vector<string> allowedCommands);

	private:
  		void start_accept();
  		void handle_accept(session* new_session,const boost::system::error_code& error);
  		boost::asio::io_service& io_service_;
  		tcp::acceptor acceptor_;
		unsigned short port;
		unsigned int time_out;
		vector<string> allowedCommands;		
};
