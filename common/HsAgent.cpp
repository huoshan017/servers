#include "HsAgent.h"
#include "hs_net_agent.h"

HsAgent::HsAgent(hs_net_agent* agent) : agent_(agent)
{
}

HsAgent::~HsAgent()
{
}

int HsAgent::Send(const char* buf, int len)
{
	return hs_net_agent_write(agent_, buf, len);
}

int HsAgent::Close()
{
	return hs_net_agent_close(agent_);
}
