#include "../incl/execShell.hpp"

string ExecShell::exec(string cmd, unsigned int time_out) 
{
	string res = cmd;
	bool canceled = false;
	boost::thread t(executionThread,&res, &canceled);
	unsigned int it=0;
	while(canceled==false && it<time_out)
	{
		it++;
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	t.interrupt();
	if(canceled==false)
		res="Telnet Demon: Time out\n";
	return res;
}

string ExecShell::getNameOfUtility(string str) 
{
	string result;	
	istringstream iss(str);
	iss >> result;
    	return result;
}

void ExecShell::executionThread(string *cmd, bool *canceled)
{
	FILE* pipe = popen(cmd->c_str(), "r");
	if (!pipe) return ;
	int buffer;
	std::string result = "";
    	while(!feof(pipe)) {
    		if((buffer = fgetc(pipe)) != EOF)
		{
    			result += char(buffer);
		}	
    	}
    	pclose(pipe);
    	*cmd = result;
	*canceled=true;
}

