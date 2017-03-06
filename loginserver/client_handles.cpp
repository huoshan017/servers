#include "client_handles.h"
#include "HsAgent.h"
#include "hs_log.h"
#include "login.pb.h"

int ClientHandles::DoLogin(HsAgent* agent, char* data, int len)
{
	MsgLoginRequest req;
	if (!req.ParseFromArray(data, len)) {
		HsLogError("parse login request failed!");
		return -1;
	}
	req.name();
	req.password();
	// 验证账号密码
	// 
	// 
	
	MsgLoginResponse rsp;
	rsp.error();

	char buffer[1024];
	if (!rsp.SerializeToArray(buffer, sizeof(buffer))) {
		HsLogError("serialize login response failed!");
		return -1;
	}

	int res = agent->Send(buffer, rsp.ByteSize());
	if (res < 0) {
		return -1;
	}
	return res;
}

int ClientHandles::DoPushServerList(HsAgent* agent, char* data, int len) {
	return 0;
}
