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

void session::setParam(unsigned short port, unsigned int time_out)
{
	this->port=port;
	this->time_out=time_out;
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
		vector<string> buf = ConfigFile::getInstance().getApps();
		if (std::find(buf.begin(), buf.end(), utilName) != buf.end())
		{
			for(int i=0; i<max_length; i++)
			{
				if(data_[i]==13 || data_[i]==10)
				{
					data_[i]=0;
					break;
				}
			}
			string str = data_;
			resOfEx = es.exec(str, this->time_out);
			resOfEx +='#';
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
      		socket_.close();
		return;
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
      		socket_.close();
		return;
    	}
}

void TelnetServer::start_accept()
{
	session* new_session = new session(io_service_);
	new_session->setParam(this->port, this->time_out);
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
