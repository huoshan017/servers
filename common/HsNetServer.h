#ifndef __HS_NET_SERVER_CPP_H__
#define __HS_NET_SERVER_CPP_H__

#include <unordered_map>
using namespace std;
#include "HsMessageHandler.h"
#include "DataType.h"

struct hs_net_agent;
struct hs_net_server;
class HsAgent;

class HsNetServer
{
public:
	HsNetServer();
	~HsNetServer();

	// 初始化时调用创建好所有的HsNetHandler实例，线程安全
	bool Create(unsigned short port, unsigned int max_agent_size);
	// 销毁时调用
	void Destroy();
	// 关闭
	void Close();
	// 载入配置
	bool loadConfig(const HsNetServerConfig* config);
	// 主循环
	int Run();

protected:
	// 载入处理函数
	bool loadHandles(const HsHandlePair* pairs, int len);
	bool AddAgent(hs_net_agent* agent);
	bool RemoveAgent(int socket);
	HsAgent* GetAgent(int socket);
	static int HandleData(char* buf, int len, void* param, void* param2);

protected:
	hs_net_server* hs_;
	unordered_map<int, HsAgent*> agents_;
	HsMessageHandler message_handler_;
	friend class HsNetServerMgr;
};

#endif
