#include "HsNetHandler.h"
#include <stddef.h>
#include "hs_net_server.h"
#include "HsAgent.h"

unordered_map<int, HsNetHandler*> HsNetHandler::servers_;

HsNetHandler::HsNetHandler() : hs_(NULL)
{
}

HsNetHandler::~HsNetHandler()
{
}

bool HsNetHandler::Create(unsigned short port, unsigned int max_agent_size)
{
	hs_ = hs_net_server_create(port, max_agent_size);
	if (!hs_) {
		return false;
	}
	hs_net_server_data_handler(hs_, HandleData);
	servers_.insert(make_pair(hs_->listen_socket, this));
	return true;
}

void HsNetHandler::Destroy()
{
	if (hs_) {
		servers_.erase(hs_->listen_socket);
		hs_net_server_destroy(hs_);
		hs_ = NULL;
	}
}

void HsNetHandler::Close()
{
}

int HsNetHandler::Run()
{
	return 1;
}

bool HsNetHandler::AddAgent(hs_net_agent* agent)
{
	HsAgent* a = new HsAgent(agent);
	if (agents_.find(agent->socket) != agents_.end()) {
		return false;
	}
	agents_.insert(make_pair(agent->socket, a));
	return true;
}

HsAgent* HsNetHandler::GetAgent(int socket)
{
	unordered_map<int, HsAgent*>::iterator it = agents_.find(socket);
	if (it == agents_.end()) {
		return NULL;
	}
	return it->second;
}

bool HsNetHandler::RemoveAgent(int socket)
{
	HsAgent* a = GetAgent(socket);
	if (a) {
		delete a;
	}
	agents_.erase(socket);

	return true;
}

int HsNetHandler::HandleData(char* buf, int len, void* param, void* param2)
{
	if (!param || !param2) {
		return -1;
	}

	if (len < 2) {
		return 0;
	}

	hs_net_server* server = (hs_net_server*)param;
	unordered_map<int, HsNetHandler*>::iterator it = servers_.find(server->listen_socket);
	if (it == servers_.end()) {
		return -1;
	}
	HsNetHandler* s = it->second;
	hs_net_agent* agent = (hs_net_agent*)param2;
	HsAgent* a = s->GetAgent(agent->socket);
	
	int nhandled = 0;
	while (true) {
		int headlen = (buf[0]<<8)&0xff00 + buf[1]&0xff;
		int res = 0;
		if (headlen > 0) {
			res = s->Handle(a, buf+nhandled+2, len-nhandled);
			if (res <= 0) {
				break;
			}
		}

		nhandled += (res+2);
		if (nhandled >= len) {
			break;
		}
	}
	return nhandled;
}
