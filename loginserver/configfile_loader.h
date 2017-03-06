#ifndef __CONFIG_FILE_LOADER_H__
#define __CONFIG_FILE_LOADER_H__

#include <string>
using namespace std;
#include "HsSingleton.hpp"

class ConfigFileLoader : public HsSingleton<ConfigFileLoader>
{
public:
	ConfigFileLoader();
	~ConfigFileLoader();

	bool load(const char* file_path);

	const char* getIP() { return ip_.c_str(); }
	unsigned short getPort() { return port_; }
	int getMaxAgentCount() { return max_agent_count_; } 

private:
	string ip_;
	unsigned short port_;
	int max_agent_count_;
};

#endif
