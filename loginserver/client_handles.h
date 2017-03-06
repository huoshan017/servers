#ifndef __CLIENT_HANDLES_H__
#define __CLIENT_HANDLES_H__

class HsAgent;

class ClientHandles
{
public:
	static int DoLogin(HsAgent*, char*, int);
	static int DoPushServerList(HsAgent*, char*, int);
	static int DoSelectServer(HsAgent*, char*, int);
};

#endif
