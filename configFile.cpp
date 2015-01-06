#include "./configFile.hpp"
ConfigFile ConfigFile::instance;

ConfigFile::ConfigFile()
{
	string str;
	this->nameOfFile= "/etc/remote-runnerd.conf";
	this->configFile.open("/etc/remote-runnerd.conf");
	while (getline(this->configFile, str))
	{
    		this->apps.push_back(str);
	}
	this->configFile.close();
	signal(SIGHUP, static_handler_sighup);
}

ConfigFile::ConfigFile(string nameOfFile)
{
	string str;
	this->nameOfFile= nameOfFile;
	this->configFile.open(nameOfFile.c_str());
	while (getline(this->configFile, str))
	{
    		this->apps.push_back(str);
	}
	this->configFile.close();
	signal(SIGHUP, static_handler_sighup);
}

ConfigFile::~ConfigFile()
{

	try
	{
		this->configFile.close();
	}
	catch(exception &e)
	{
		cout<<"Nothing to close"<<endl;
	}
	try
	{
		this->apps.clear();
	}
	catch(exception &e)
	{
		cout<<"Nothing to clear"<<endl;
	}
}

vector<string> ConfigFile::getApps()
{
	return this->apps;
}

int ConfigFile::update()
{
	int i=0;
	string str;
	try
	{
		this->apps.clear();
	}
	catch(exception &e)
	{
	}
	this->configFile.open(nameOfFile.c_str());
	while (getline(this->configFile, str))
	{
    		this->apps.push_back(str);
		i++;
	}
	this->configFile.close();
	return i;
}

void ConfigFile::handler_sighup(int sig)
{
	cout<<"SIGHUP signal catched"<<endl;
	update();
}

void ConfigFile::static_handler_sighup(int sig)
{
	instance.handler_sighup(sig);
}
