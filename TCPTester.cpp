#include "Particle.h"

#include "TCPTester.h"

TCPTester::TCPTester(IPAddress serverAddr, int serverPort) : serverAddr(serverAddr), serverPort(serverPort) {

}

TCPTester::~TCPTester() {

}

void TCPTester::setup() {

}
void TCPTester::loop() {
	stateHandler(*this);
}

void TCPTester::startState() {
	if (Particle.connected()) {
		stateHandler = &TCPTester::connectState;
	}
}

void TCPTester::connectState() {
	Log.info("connecting to %s:%d", serverAddr.toString().c_str(), serverPort);

	if (connect(serverAddr, serverPort)) {
		Log.info("connected");
		stateTime = millis();
		stateHandler = &TCPTester::runState;
	}
	else {
		Log.info("failed to connect");
		stateTime = millis();
		stateHandler = &TCPTester::retryWaitState;
	}
}

void TCPTester::runState() {
	if (connected()) {
		while(available()) {
			int c = read();
			Log.info("got 0x%02x", c);
		}

		if (millis() - stateTime >= SEND_TIME_MS) {
			stateTime = millis();
			Log.info("sending 0x%02x", nextValue);
			write(nextValue++);
		}
	}
	else {
		// Disconnected
		Log.info("disconnected");
		stateTime = millis();
		stateHandler = &TCPTester::retryWaitState;
	}
}

void TCPTester::retryWaitState() {
	if (millis() - stateTime >= RETRY_TIME_MS) {
		stateHandler = &TCPTester::connectState;
	}
}




