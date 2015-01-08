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
#include "./configFile.hpp"

using boost::asio::local::stream_protocol;

using namespace std;
#define DEFAULT_PORT 12345
#define VERSION "Telnet demon version 0.0.0.1.a"
class lsession
{
	public:
  		lsession(boost::asio::io_service& io_service): socket_(io_service){memset(data_, 0,max_length);};
		~lsession(){socket_.close();};
  		stream_protocol::socket& socket();
  		void start();
		void setParam(string port, unsigned int time_out);
	private:
  		void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
  		void handle_write(const boost::system::error_code& error);
  		stream_protocol::socket socket_;
  		enum { max_length = 65536 };
  		char data_[max_length];
		string port;
		unsigned int time_out;
};

class LocalServer
{
	public:
		LocalServer(boost::asio::io_service& io_service, string localPort, unsigned int time_out, string PathToConfigFile)
    		: io_service_(io_service), acceptor_(io_service, stream_protocol::endpoint(localPort))
  		{
			this->localPort = localPort;
			this->time_out = time_out;
			ConfigFile::getInstance().open(PathToConfigFile);
    			start_accept();
  		};
		~LocalServer(){::unlink(localPort.c_str());};

	private:
  		void start_accept();
  		void handle_accept(lsession* new_session,const boost::system::error_code& error);
  		boost::asio::io_service& io_service_;
  		stream_protocol::acceptor acceptor_;
		stream_protocol::endpoint ep;
		unsigned int time_out;
		string localPort;	
};
