#ifndef __HS_NET_SERVER_H__
#define __HS_NET_SERVER_H__

#include <unordered_map>
using namespace std;

struct hs_net_agent;
struct hs_net_server;
class HsAgent;

typedef int (*HsMsgHandle)(HsAgent*, char*, int);

struct HsHandlePair {
	int msg_id;
	HsMsgHandle msg_handle;
};

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
	// 载入处理函数
	bool LoadHandles(struct HsHandlePair* pairs, int len);
	// 主循环
	int Run();
	// 获取消息ID
	virtual int getMsgID(char*, int, int&);
	// 处理函数
	int Handle(HsAgent* , char* , int );

protected:
	bool AddAgent(hs_net_agent* agent);
	bool RemoveAgent(int socket);
	HsAgent* GetAgent(int socket);
	static int HandleData(char* buf, int len, void* param, void* param2);

protected:
	hs_net_server* hs_;
	unordered_map<int, HsAgent*> agents_;
	static unordered_map<int, HsNetServer*> servers_;
	unordered_map<int, HsMsgHandle> handles_;
};

#endif
