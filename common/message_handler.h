#ifndef __MESSAGE_HANDLER_H__
#define __MESSAGE_HANDLER_H__

#include <unordered_map>
using namespace std;

class HsNetServer;
class HsAgent;

typedef void (*HandleFunc)(HsNetServer*, HsAgent*, const char*, int);

class MessageHandler {
public:
	virtual void Dispatch(HsNetServer* server, HsAgent* agent, const char* buf, int len) {}
	
protected:
	void RegisterHandler(int id, HandleFunc handle) {
		if (handle_maps_.find(id) != handle_maps_.end()) {
			return;
		}

		handle_maps_.insert(make_pair(id, handle));
	}

	static unordered_map<int, HandleFunc> handle_maps_;
};

#endif
