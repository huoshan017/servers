#include "HsNetServerMgr.h"
#include "HsNetServer.h"
#include "hs_net_server.h"

HsNetServerMgr::HsNetServerMgr()
{
}

HsNetServerMgr::~HsNetServerMgr()
{
}

void HsNetServerMgr::Clear()
{
	servers_.clear();
}

bool HsNetServerMgr::addServer(HsNetServer* server)
{
	if (!server) return false;

	hs_net_server* hs = server->hs_;
	if (!hs) return false;
	unordered_map<int, HsNetServer*>::iterator it = servers_.find(hs->listen_socket);
	if (it == servers_.end())
		return false;

	servers_.insert(make_pair(hs->listen_socket, server));

	return true;
}

bool HsNetServerMgr::removeServer(int sock_fd)
{
	unordered_map<int, HsNetServer*>::iterator it = servers_.find(sock_fd);
	if (it == servers_.end())
		return false;
	servers_.erase(it);
	return true;
}

HsNetServer* HsNetServerMgr::getServer(int sock_fd)
{
	unordered_map<int, HsNetServer*>::iterator it = servers_.find(sock_fd);
	if (it == servers_.end())
		return NULL;
	return it->second;
}
