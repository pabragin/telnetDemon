#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <sstream>

using namespace std;

class ExecShell
{
	public:
		ExecShell(){};
		string exec(string cmd);
		string getNameOfUtility(string str);
};
