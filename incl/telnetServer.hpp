/*
Классы для представления сервера работы с сокетами
Данный файл содержит 2 класса:
session - для представления отдельных подключений
TelnetServer - сам сервервер
*/
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
  		session(boost::asio::io_service& io_service): socket_(io_service){memset(data_, 0,max_length);};				//Конструктор класса сессий
		~session(){socket_.close();};													//В деструкторе просто закрываем сокет
  		tcp::socket& socket();														//Получение сокета
  		void start();															//Запуск сессии
		void setParam(unsigned int time_out);												//Задание таймаута на выполнение комманд
	private:
  		void handle_read(const boost::system::error_code& error, size_t bytes_transferred);						//Обработчик операций чтения из сокета
  		void handle_write(const boost::system::error_code& error);									//Обработчик операций записи в сокет
  		tcp::socket socket_;				
  		enum { max_length = 65536 };
  		char data_[max_length];
		unsigned int time_out;
};

class TelnetServer
{
	public:
  		TelnetServer(boost::asio::io_service& io_service, unsigned short port, unsigned int time_out, string PathToConfigFile)		//Конструтруктор демона TCP
    		: io_service_(io_service),acceptor_(io_service, tcp::endpoint(tcp::v4(), port))							//Создать приемник подключений
  		{
			this->port = port;
			this->time_out = time_out;
			ConfigFile::getInstance().open(PathToConfigFile);									//Прочесть конфигурационный файл
    			start_accept();														//Запустить приемник
  		};
	private:
  		void start_accept();
  		void handle_accept(session* new_session,const boost::system::error_code& error);
  		boost::asio::io_service& io_service_;
  		tcp::acceptor acceptor_;
		unsigned short port;
		unsigned int time_out;
		string localPort;	
};
