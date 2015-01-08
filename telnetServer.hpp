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

using boost::asio::ip::tcp;

using namespace std;
#define DEFAULT_PORT 12345
#define VERSION "Telnet demon version 0.0.0.1.a"
class session
{
	public:
  		session(boost::asio::io_service& io_service): socket_(io_service){memset(data_, 0,max_length);};
		~session(){socket_.close();};
  		tcp::socket& socket();
  		void start();
		void setParam(unsigned short port, unsigned int time_out);
	private:
  		void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
  		void handle_write(const boost::system::error_code& error);
  		tcp::socket socket_;
  		enum { max_length = 65536 };
  		char data_[max_length];
		unsigned short port;
		unsigned int time_out;
};

class TelnetServer
{
	public:
  		TelnetServer(boost::asio::io_service& io_service, unsigned short port, unsigned int time_out, string PathToConfigFile)
    		: io_service_(io_service),acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
  		{
			this->port = port;
			this->time_out = time_out;
			ConfigFile::getInstance().open(PathToConfigFile);
    			start_accept();
  		}

	private:
  		void start_accept();
  		void handle_accept(session* new_session,const boost::system::error_code& error);
  		boost::asio::io_service& io_service_;
  		tcp::acceptor acceptor_;
		unsigned short port;
		unsigned int time_out;
		//ConfigFile &configFile;	
		//static TelnetServer instance;
		//void handler_sighup(int sig);
		//static void static_handler_sighup(int sig);	
};
