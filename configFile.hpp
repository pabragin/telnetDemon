#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <signal.h>

using namespace std;

class ConfigFile{
	public:
		vector<string> getApps();
		int update();
		int open(string PATH);
		static ConfigFile& getInstance() {
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
		void handler_sighup(int sig);
		static void static_handler_sighup(int sig);
};
