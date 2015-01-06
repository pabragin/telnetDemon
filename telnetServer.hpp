#include <boost/asio.hpp> 
#include <string> 

class TelnetServer
{
	public:
		TelnetServer();
		TelnetServer(unsigned short port, unsigned int time_out, vector<string> apps);
		~TelnetServer();
	private:
		boost::asio::io_service io_service; 
		boost::asio::ip::tcp::endpoint endpoint; 
		boost::asio::ip::tcp::acceptor acceptor; 
		boost::asio::ip::tcp::socket sock;
}
