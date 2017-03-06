#include "configfile_loader.h"
#include <memory.h>
#include <fstream>
#include <iostream>
#include <cassert>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "hs_log.h"

ConfigFileLoader::ConfigFileLoader() : port_(0), max_agent_count_(0)
{
}

ConfigFileLoader::~ConfigFileLoader()
{
}

bool ConfigFileLoader::load(const char* file_path)
{
	using std::ifstream;
	// read json
	fstream in(file_path);
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
	ip_ = v.GetString();

	v = doc["port"];
	if (!v.IsUint()) {
		HsLogError("get port failed\n");
		return false;
	}
	port_ = (unsigned short)(v.GetUint());

	v = doc["max_agent_count"];
	if (!v.IsUint()) {
		HsLogError("get max_agent_count failed!");
		return false;
	}
	max_agent_count_ = v.GetUint();
	HsLogInfo("get ip(%s) port(%d) max_agent_count(%d)", ip_.c_str(), port_, max_agent_count_);
	return true;
}
