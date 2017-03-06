#ifndef __CONST_H__
#define __CONST_H__

#include "DataType.h"
#include "login.pb.h"
#include "client_handles.h"

const static int MAX_HANDLE_BUFFER_SIZE = 1024*16;

const static HsHandlePair s_clients_handle_pairs[] = {
	{ MSG_ID_LS2C_LOGIN_RESPONSE, 			  ClientHandles::DoLogin 			},
	{ MSG_ID_LS2C_GAMESERVERLIST_RESPONSE,    ClientHandles::DoPushServerList 	}
};

const static HsNetServerConfig s_clients_config = {
	s_clients_handle_pairs,
	sizeof(s_clients_handle_pairs)/sizeof(s_clients_handle_pairs[0])
};

#endif
