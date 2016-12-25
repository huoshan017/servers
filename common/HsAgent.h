#ifndef __HS_AGENT_H__
#define __HS_AGENT_H__

struct hs_net_agent;

class HsAgent
{
public:
	HsAgent(hs_net_agent* agent);
	~HsAgent();

	int Send(const char* buf, int len);
	int Close();

private:
	hs_net_agent* agent_;
};

#endif
