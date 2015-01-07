#include "./execShell.hpp"

string ExecShell::exec(string cmd) {
	FILE* pipe = popen(cmd.c_str(), "r");
	if (!pipe) return "ERROR";
	int buffer;
	std::string result = "";
    	while(!feof(pipe)) {
    		if((buffer = fgetc(pipe)) != EOF)
		{
    			result += char(buffer);
		}	
    	}
    	pclose(pipe);
    	return result;
}

string ExecShell::getNameOfUtility(string str) {
	string result;	
	istringstream iss(str);
	iss >> result;
    	return result;
}

