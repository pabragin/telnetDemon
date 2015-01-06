#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <signal.h>

using namespace std;

class ConfigFile{
	public:
		ConfigFile();
		ConfigFile(string nameOfFile);
		~ConfigFile();
		vector<string> getApps();
		int update();
	private:
		vector<string> apps;
		ifstream configFile;
		string nameOfFile;
		static ConfigFile instance;
		void handler_sighup(int sig);
		static void static_handler_sighup(int sig);
};
