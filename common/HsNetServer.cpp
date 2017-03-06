#include "HsNetServer.h"
#include <stddef.h>
#include "hs_net_server.h"
#include "HsAgent.h"
#include "HsNetServerMgr.h"
#include "hs_log.h"

HsNetServer::HsNetServer() : hs_(NULL)
{
}

HsNetServer::~HsNetServer()
{
}

bool HsNetServer::Create(unsigned short port, unsigned int max_agent_size)
{
	hs_ = hs_net_server_create(port, max_agent_size);
	if (!hs_) {
		return false;
	}
	hs_net_server_data_handler(hs_, HandleData);
	HsNetServerMgr::getInstance()->addServer(this);
	return true;
}

void HsNetServer::Destroy()
{
	if (hs_) {
		if (!HsNetServerMgr::getInstance()->removeServer(hs_->listen_socket)) {
			HsLogWarn("remove server(%d) failed!", hs_->listen_socket);
		}
		hs_net_server_destroy(hs_);
		hs_ = NULL;
	}
}

void HsNetServer::Close()
{
	if (hs_) {
		hs_net_server_close(hs_);
	}
}

bool HsNetServer::loadConfig(const HsNetServerConfig* config)
{
	if (loadHandles(config->pairs, config->npairs)) {
		return false;
	}
	return true;
}

bool HsNetServer::loadHandles(const HsHandlePair* pairs, int len)
{
	if (len <= 0) {
		return false;
	}

	int i = 0;
	for (; i<len; i++) {
		message_handler_.addHandle(pairs[i].msg_id, pairs[i].msg_handle);
	}

	return true;
}

int HsNetServer::Run()
{
	if (!hs_) {
		return -1;
	}
	return hs_net_server_run(hs_);
}

bool HsNetServer::AddAgent(hs_net_agent* agent)
{
	HsAgent* a = new HsAgent(agent);
	if (agents_.find(agent->socket) != agents_.end()) {
		return false;
	}
	agents_.insert(make_pair(agent->socket, a));
	return true;
}

HsAgent* HsNetServer::GetAgent(int socket)
{
	unordered_map<int, HsAgent*>::iterator it = agents_.find(socket);
	if (it == agents_.end()) {
		return NULL;
	}
	return it->second;
}

bool HsNetServer::RemoveAgent(int socket)
{
	HsAgent* a = GetAgent(socket);
	if (a) {
		delete a;
	}
	agents_.erase(socket);

	return true;
}

int HsNetServer::HandleData(char* buf, int len, void* param, void* param2)
{
	if (!param || !param2) {
		HsLogWarn("param(%d) or param(%d) is null", (int)(uint64_t)param, (int)(uint64_t)param2);
		return -1;
	}

	if (len < 2) {
		HsLogDebug("data len(%d) not enough to get one message, at lease need %d", len, 2);
		return 0;
	}

	// param is the type of hs_net_server*
	hs_net_server* server = (hs_net_server*)param;
	HsNetServer* s = HsNetServerMgr::getInstance()->getServer(server->listen_socket);
	if (!s) {
		HsLogWarn("not found listen socket(%d) server", server->listen_socket);
		return -1;
	}
	// param2 is the type of hs_net_agent*
	hs_net_agent* agent = (hs_net_agent*)param2;
	HsAgent* a = s->GetAgent(agent->socket);
	
	int nhandled = 0;
	while (true) {
		// 包长
		uint16_t msg_len = (uint16_t)((buf[nhandled]<<8)&0xff00 + buf[nhandled+1]&0xff);
		
		uint16_t left = len - nhandled - 2;
		// 剩余长度不够一条消息
		if (left < msg_len) {
			HsLogInfo("wait to receive new data to handle (msg_len:%d, left_len:%d)", msg_len, left);
			break;
		}
		// 消息处理，返回值为处理的长度
		int res = s->message_handler_.dispatch(a, buf+nhandled+2, msg_len);
		if (res < 0) {
			HsLogWarn("Handle return %d", res);
			break;
		}

		nhandled += (2+msg_len);
		if (len - nhandled < 2) {
			HsLogDebug("next head len(%d) not enough", len-nhandled);
			break;
		}
	}
	return nhandled;
}
