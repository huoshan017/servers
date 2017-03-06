#include "loginserver.h"
#include <iostream>

int main(int argc, char** argv) {
	LoginServer* ls = new LoginServer;
	if (!ls) {
		cout << "create login server failed!" << endl;
	}
	if (!ls->Init())
		return -1;

	if (ls->Run() < 0) {
		return -1;
	}

	delete ls;

	return 0;
}
