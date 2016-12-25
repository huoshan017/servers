#ifndef __HS_NET_HANDLER_H__
#define __HS_NET_HANDLER_H__

#include <unordered_map>
using namespace std;

struct hs_net_agent;
struct hs_net_server;
class HsAgent;
class HsNetHandler
{
public:
	HsNetHandler();
	~HsNetHandler();

	bool Create(unsigned short port, unsigned int max_agent_size);
	void Destroy();
	void Close();
	int Run();
	virtual int Handle(HsAgent* , char* , int ) { return 0; }

protected:
	bool AddAgent(hs_net_agent* agent);
	bool RemoveAgent(int socket);
	HsAgent* GetAgent(int socket);
	static int HandleData(char* buf, int len, void* param, void* param2);

protected:
	hs_net_server* hs_;
	unordered_map<int, HsAgent*> agents_;
	static unordered_map<int, HsNetHandler*> servers_;
};

#endif
