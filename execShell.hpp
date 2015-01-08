#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

using namespace std;

class ExecShell
{
	public:
		ExecShell(){};
		string exec(string cmd, unsigned int time_out);
		string getNameOfUtility(string str);
	private:
		void executionThread(string *cmdRes, bool *canceled);
};
