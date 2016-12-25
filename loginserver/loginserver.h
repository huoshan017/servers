#ifndef __LOGIN_SERVER_H__
#define __LOGIN_SERVER_H__

#include <string>
using namespace std;

class HsNetHandler;

class LoginServer 
{
public:
	LoginServer();
	~LoginServer();
	
	bool Init();
	void Destroy();
	int Run();

private:
	void InitMem();
	bool ReadConfig();

private:
	HsNetHandler* clients_handler_;
	HsNetHandler* games_handler_;

	struct Config {
		string ip;
		unsigned short port;
		int max_agent_count;

		Config() : port(0), max_agent_count(0) {
		}
	} config_;
};

#endif
