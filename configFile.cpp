#include "./configFile.hpp"

vector<string> ConfigFile::getApps()
{
	return getInstance().apps;
}

int ConfigFile::update()
{
	int i=0;
	string str;
	try
	{
		getInstance().apps.clear();
	}
	catch(exception &e)
	{
	}
	getInstance().configFile.open(nameOfFile.c_str());
	while (getline(getInstance().configFile, str))
	{
    		getInstance().apps.push_back(str);
		i++;
	}
	getInstance().configFile.close();
	cout<<"Config file update"<<endl;
	return i;
}

int ConfigFile::open(string nameOfFile)
{
	int i=0;
	string str;
	getInstance().nameOfFile= nameOfFile;
	getInstance().configFile.open(nameOfFile.c_str());
	while (getline(getInstance().configFile, str))
	{
    		getInstance().apps.push_back(str);
		i++;
	}
	getInstance().configFile.close();
	signal(SIGHUP, static_handler_sighup);
	return i;
}

void ConfigFile::handler_sighup(int sig)
{
	cout<<"SIGHUP signal catched"<<endl;
	update();
}

void ConfigFile::static_handler_sighup(int sig)
{
	getInstance().handler_sighup(sig);
}
