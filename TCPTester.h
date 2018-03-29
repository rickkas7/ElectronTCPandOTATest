#ifndef __TCPTESTER_H
#define __TCPTESTER_H

#include "Particle.h"

class TCPTester : public TCPClient {
public:
	TCPTester(IPAddress serverAddr, int serverPort);
	virtual ~TCPTester();

	void setup();
	void loop();

private:
	void startState();
	void connectState();
	void runState();
	void retryWaitState();

	static const unsigned long START_TIME_MS = 5000;
	static const unsigned long RETRY_TIME_MS = 15000;
	static const unsigned long SEND_TIME_MS = 5000;

	std::function<void(TCPTester&)> stateHandler = &TCPTester::startState;
	IPAddress serverAddr;
	int serverPort;
	unsigned long stateTime = 0;
	uint8_t nextValue = 0;
};

#endif /* __TCPTESTER_H */
