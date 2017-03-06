#ifndef __HS_MESSAGE_HANDLER_H__
#define	__HS_MESSAGE_HANDLER_H__

#include <stdint.h>
#include <unordered_map>
using namespace std;
#include "DataType.h"
#include "HsAgent.h"

class HsMessageHandler
{
public:
	HsMessageHandler();
	~HsMessageHandler();

	void clear();
	bool addHandle(uint32_t, HsMsgHandle);
	int dispatch(HsAgent*, char*, int);

protected:
	virtual int getMsgID(char* data, int len, int& used_len);

private:
	unordered_map<uint32_t, HsMsgHandle> handles_;
};

#endif
