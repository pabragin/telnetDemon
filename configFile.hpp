/*
Класс для представления конфигурационного файла
По сути хранит в себе набор разрешенных для запуска утилит
В нем же реализована обработка сигнала SIGHUP  и обнвление
данных при получении данного сигнала.
*/
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <signal.h>

using namespace std;

class ConfigFile{
	public:
		vector<string> getApps();		//Функция получения всех разрешенных утилит
		int update();				//Обновление данных конфигурационного файла
		int open(string PATH);			//Открытие конфигурационного файла, выполняется один раз
		static ConfigFile& getInstance() {	//Получение доступа к объекту класса
        		static ConfigFile  instance;
        		return instance;
    		}
	private:
		ConfigFile(){};
		~ConfigFile(){};
		ConfigFile( const ConfigFile&);  
    		ConfigFile& operator=( ConfigFile& );
		vector<string> apps;
		ifstream configFile;
		string nameOfFile;
		void handler_sighup(int sig);			//Обработчик сигнала
		static void static_handler_sighup(int sig);
};
