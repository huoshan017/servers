#ifndef __LOGIN_SERVER_H__
#define __LOGIN_SERVER_H__

#include <string>
using namespace std;

class HsNetServer;

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
	HsNetServer* clients_handler_;
	HsNetServer* games_handler_;
};

#endif
