/*
Классы для представления сервера работы с локальными сокетами
Данный файл содержит 2 класса:
lsession - для представления отдельных локальных подключений
LocalServer - сам сервервер
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

using boost::asio::local::stream_protocol;

using namespace std;
#define DEFAULT_PORT 12345
#define VERSION "Telnet demon version 0.0.0.1.a"
class lsession
{
	public:
  		lsession(boost::asio::io_service& io_service): socket_(io_service){memset(data_, 0,max_length);};	//Конструктор класса сессий
		~lsession(){socket_.close();};										//В деструкторе просто закрываем сокет
  		stream_protocol::socket& socket();									//Получение сокета
  		void start();												//Запуск сессии
		void setParam(unsigned int time_out);									//Задание таймаута на выполнение комманд
	private:
  		void handle_read(const boost::system::error_code& error, size_t bytes_transferred);			//Обработчик операций чтения из сокета
  		void handle_write(const boost::system::error_code& error);						//Обработчик операций записи в сокет
  		stream_protocol::socket socket_;
  		enum { max_length = 65536 };
  		char data_[max_length];
		unsigned int time_out;
};

class LocalServer
{
	public:
		LocalServer(boost::asio::io_service& io_service, string localPort, unsigned int time_out, string PathToConfigFile)	//Конструтруктор сервера по работе с локальным сокетом
    		: io_service_(io_service)
  		{
			::unlink(localPort.c_str());											//освободить файл-сокет
			acceptor_ = new stream_protocol::acceptor(io_service, stream_protocol::endpoint(localPort));			//Создать приемник подключений
			this->time_out = time_out;
			ConfigFile::getInstance().open(PathToConfigFile);								//Прочесть конфигурационный файл
    			start_accept();													//Запустить приемник
  		};
		~LocalServer(){delete(acceptor_), ::unlink(localPort.c_str());};

	private:
  		void start_accept();
  		void handle_accept(lsession* new_session,const boost::system::error_code& error);
  		boost::asio::io_service& io_service_;
  		stream_protocol::acceptor *acceptor_;
		stream_protocol::endpoint ep;
		unsigned int time_out;
		string localPort;	
};
