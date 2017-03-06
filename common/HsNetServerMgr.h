#ifndef __HS_NET_SERVER_MGR_H__
#define __HS_NET_SERVER_MGR_H__

#include <unordered_map>
using namespace std;
#include "HsSingleton.hpp"

class HsNetServer;
class HsNetServerMgr : public HsSingleton<HsNetServerMgr>
{
public:
	HsNetServerMgr();
	~HsNetServerMgr();
	void Clear();

	bool addServer(HsNetServer* server);
	bool removeServer(int sock_fd);
	HsNetServer* getServer(int sock_fd);

private:
	unordered_map<int, HsNetServer*> servers_;
};

#endif
