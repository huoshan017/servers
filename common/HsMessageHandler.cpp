#include "HsMessageHandler.h"
#include "hs_log.h"

HsMessageHandler::HsMessageHandler()
{
}

HsMessageHandler::~HsMessageHandler()
{
}

void HsMessageHandler::clear()
{
	handles_.clear();
}

bool HsMessageHandler::addHandle(uint32_t msg_id, HsMsgHandle msg_handle)
{
	handles_.insert(make_pair(msg_id, msg_handle));
	return true;
}

int HsMessageHandler::dispatch(HsAgent* agent, char* data, int len)
{
	int used_len = 0;
	int msg_id = getMsgID(data, len, used_len);
	if (msg_id < 0) {
		return -1;
	}
	unordered_map<uint32_t, HsMsgHandle>::iterator it = handles_.find(msg_id);
	if (it == handles_.end()) {
		return -1;
	}
	return it->second(agent, data+used_len, len-used_len);
}

int HsMessageHandler::getMsgID(char* data, int len, int& used_len)
{
	used_len = 2;
	if (len < used_len) {
		HsLogError("len(%d) not enough, 2 at least(%u)", len, used_len);
		return -1;
	}

	int msg_id = (data[0]<<8)&0xff00+(data[1]&0xff);
	return msg_id;
}

