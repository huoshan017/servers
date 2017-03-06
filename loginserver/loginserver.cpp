#include "loginserver.h"
#include "hs_log.h"
#include "HsNetServer.h"
#include "const.h"
#include "configfile_loader.h"

LoginServer::LoginServer() : clients_handler_(NULL), games_handler_(NULL)
{
}

LoginServer::~LoginServer()
{
	string s;
}

bool LoginServer::Init()
{
	if (!hs_log_init("log.conf", "my_cat")) {
		HsLogError("Init log config failed");
		return false;
	}

	// 读取配置
	if (!ReadConfig()) {
		return false;
	}

	//const char* ip = ConfigFileLoader::getInstance()->getIP();
	unsigned short port = ConfigFileLoader::getInstance()->getPort();
	int max_agent_count = ConfigFileLoader::getInstance()->getMaxAgentCount();
	clients_handler_ = new HsNetServer;
	if (!clients_handler_->Create(port, max_agent_count)) {
		HsLogError("Create LoginServer Failed!\n");	
		return false;
	}
	if (!clients_handler_->loadConfig(&s_clients_config)) {
		return false;
	}
	return true;
}

void LoginServer::Destroy()
{
	if (clients_handler_ != NULL) {
		clients_handler_->Destroy();
		clients_handler_ = NULL;
	}
	if (games_handler_ != NULL) {
		games_handler_->Destroy();
		games_handler_ = NULL;
	}
}

int LoginServer::Run()
{
	int res = 0;
	while (true) {
		res = clients_handler_->Run();
		if (res < 0) {
			HsLogError("clients_handler_ run failed");
			break;
		}
		res = games_handler_->Run();
		if (res < 0) {
			HsLogError("games_handler_ run failed");
			break;
		}
		usleep(1000);
	}
	return res;
}

bool LoginServer::ReadConfig()
{
	return ConfigFileLoader::getInstance()->load("config.json");
}
