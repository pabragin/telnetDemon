#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "./telnetServer.hpp"
#include "./localServer.hpp"

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
	bool LOCAL_PORT=false;
	unsigned short PORT_NUM = 12345;
	string PORT_PATH="/tmp/simple-telnetd";
	unsigned int TIME_OUT = 100; // in millisconds
	string PATH = "/etc/remote-runnerd.conf";
	int rez=0;

	while ( (rez = getopt(argc,argv,"lp:f:t:h")) != -1){
		switch (rez){
			case 'l': LOCAL_PORT=true; break;
			case 'p':
				if(LOCAL_PORT==false)
				{
					try
            				{
						PORT_NUM = lexical_cast<unsigned short>(optarg); 
						cout << "PORT is "<< PORT_NUM<<endl;
            				}
            				catch(const bad_lexical_cast& e)
            				{
						cout << "Wrong port number "<< optarg<<", using PORT "<< PORT_NUM<<endl;
					}
				}
				else
				{
					try
            				{
						PORT_PATH = lexical_cast<string>(optarg); 
						cout << "PORT PATH is "<< PORT_PATH<<endl;
            				}
            				catch(const bad_lexical_cast& e)
            				{
						cout << "Wrong port path "<< optarg<<", using PORT PATH"<< PORT_PATH<<endl;
					}
				}
				break;
			case 'f':
				try
            			{
					PATH = lexical_cast<string>(optarg); 
					cout << "PATH is "<< PATH<<endl;
            			}
            			catch(const bad_lexical_cast& e)
            			{
					cout << "Wrong path "<< optarg<<", using PATH "<< PATH<<endl;
				} 
				break;
			case 't':
				try
            			{
					TIME_OUT = lexical_cast<unsigned int>(optarg); 
					cout << "Time out is "<< TIME_OUT<< " ms"<<endl;
            			}
            			catch(const bad_lexical_cast& e)
            			{
					cout << "Wrong time out "<< optarg<<", using TIME_OUT "<< TIME_OUT<<" ms"<<endl;
				} 
				break;
			case 'h': 
				cout << "-l - use this option for local ports. Set this option before '-p' (default dont use local ports)"<<endl;
				cout << "-p - set port number or port path according to -l option(default '12345' or '/tmp/simple-telnetd' if -l option enabled)"<<endl;
				cout << "-f - path to file with alowed apps (default '/etc/remote-runnerd.conf')"<<endl;
				cout << "-t - timeout in milliseconds (default '100')"<<endl;
				cout << "-h - help message"<<endl;
				cout << "Example: telnetDemon -p 12345 -f /etc/remote-runnerd.conf -t 100"<<endl;
				cout << "or"<<endl;
				cout << "telnetDemon -l -p  /tmp/simple-telnetd -f /etc/remote-runnerd.conf -t 100"<<endl;
				break;
			case '?': cout << "Usage: telnetDemon -l -p [port_num] -f [path_to_file] -t [time_out] -h"<<endl; break;
        	};
	};
	boost::asio::io_service io_service;
	if(LOCAL_PORT==false)
	{
		TelnetServer ts(io_service, PORT_NUM, TIME_OUT, PATH);
		io_service.run();
	}
	else
	{
		LocalServer ls(io_service, PORT_PATH, TIME_OUT, PATH);
		io_service.run();
	}
	return 0;
};
