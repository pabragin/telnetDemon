#include "./telnetServer.hpp"

tcp::socket& session::socket()
{
	return socket_;
}

void session::start()
{
	boost::asio::async_write(socket_,
        boost::asio::buffer("#", 1),
        boost::bind(&session::handle_write, this,
        boost::asio::placeholders::error));
}

void session::setParam(unsigned short port, unsigned int time_out, vector<string> allowedCommands)
{
	this->port=port;
	this->time_out=time_out;
	this->allowedCommands=allowedCommands;
}

void session::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (!error)
    	{
		if(strncmp ( data_, "quit", 4 )==0)
		{
			socket_.close();
			return;
		}
		ExecShell es;
		string utilName = es.getNameOfUtility(data_);
		string resOfEx = "";
		if (std::find(this->allowedCommands.begin(), this->allowedCommands.end(), utilName) != this->allowedCommands.end())
		{
			for(int i=0; i<max_length; i++)
			{
				if(data_[i]<0x020 || data_[i]>0x7e)
					data_[i]=0;
			}
			string str = data_;
			//if (str.size () > 1)  str.resize (str.size () - 2);
			resOfEx = es.exec(str)+'#';
		}
		else
		{
			resOfEx = utilName + " dont permitted"+'\n'+'#';
		} 
      		boost::asio::async_write(socket_,
          	boost::asio::buffer(resOfEx, resOfEx.size()),
          	boost::bind(&session::handle_write, this,
            	boost::asio::placeholders::error));
    	}
    	else
    	{
      		delete this;
    	}
}

void session::handle_write(const boost::system::error_code& error)
{
	if (!error)
    	{
		memset(data_, 0,max_length);
      		socket_.async_read_some(boost::asio::buffer(data_, max_length),
          	boost::bind(&session::handle_read, this,
            	boost::asio::placeholders::error,
            	boost::asio::placeholders::bytes_transferred));
    	}
    	else
    	{
      		delete this;
    	}
}

void TelnetServer::start_accept()
{
	session* new_session = new session(io_service_);
	new_session->setParam(this->port, this->time_out, this->allowedCommands);
    	acceptor_.async_accept(new_session->socket(),
        boost::bind(&TelnetServer::handle_accept, this, new_session,
        boost::asio::placeholders::error));
}

void TelnetServer::handle_accept(session* new_session,const boost::system::error_code& error)
{
	if (!error)
    	{
      		new_session->start();
    	}
    	else
    	{
      		delete new_session;
    	}
    	start_accept();
}
