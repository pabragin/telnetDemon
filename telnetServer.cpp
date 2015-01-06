#include "./telnetServer.hpp"

#define PORT 12345

void TelnetServer::write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) 
{ 
} 

void TelnetServer::accept_handler(const boost::system::error_code &ec) 
{ 
  if (!ec) 
  { 
    boost::asio::async_write(sock, boost::asio::buffer(data), write_handler);
     
  } 
} 

TelnetServer::TelnetServer() 
{ 
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), PORT); 
	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint); 
	boost::asio::ip::tcp::socket sock(io_service); 
  	acceptor.listen(); 
  	acceptor.async_accept(sock, accept_handler); 
  	io_service.run(); 
} 
