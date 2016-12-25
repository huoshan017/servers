#include "loginserver.h"
#include "hs_log.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include "HsNetHandler.h"

LoginServer::LoginServer() : clients_handler_(NULL), games_handler_(NULL)
{
}

LoginServer::~LoginServer()
{
	string s;
}

bool LoginServer::Init()
{
	char* ip = NULL;
	unsigned short port = 0;

	if (!hs_log_init("log.conf", "my_cat")) {
		cout << "Init log config failed" << endl;
		return false;
	}

	// 读取配置
	if (!ReadConfig()) {
		return false;
	}

	clients_handler_ = new HsNetHandler();	
	if (!clients_handler_->Create(config_.port, config_.max_agent_count)) {
		HsLogError("Create LoginServer Failed!\n");	
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
			HsLogError("LoginServer Run Failed!\n");
			break;
		}
		usleep(1000);
	}
	return res;
}

bool LoginServer::ReadConfig()
{
	using std::ifstream;
	// read json
	fstream in("config.json");
	if (!in.is_open()) {
		HsLogError("config json can not open!\n");
		return false;
	}

	char buf[256];
	memset(buf, 0, sizeof(buf));
	in.read(buf, sizeof(buf)-1);
	using rapidjson::Document;
	Document doc;
	doc.Parse<0>(buf, (size_t)sizeof(buf)-1);
	if (doc.HasParseError()) {
		rapidjson::ParseErrorCode code = doc.GetParseError();
		HsLogError("parse json file error(%d)\n", code);
		return false;
	}
	in.close();

	using rapidjson::Value;
	// get value
	Value& v = doc["ip"];
	if (!v.IsString()) {
		HsLogError("get ip failed\n");
		return false;
	}
	config_.ip = v.GetString();

	v = doc["port"];
	if (!v.IsUint()) {
		HsLogError("get port failed\n");
		return false;
	}
	config_.port = (unsigned short)(v.GetUint());

	v = doc["max_agent_count"];
	if (!v.IsUint()) {
		HsLogError("get max_agent_count failed!");
		return false;
	}
	config_.max_agent_count = v.GetUint();
	HsLogInfo("get ip(%s) port(%d) max_agent_count(%d)", config_.ip.c_str(), config_.port, config_.max_agent_count);
	return true;
}
