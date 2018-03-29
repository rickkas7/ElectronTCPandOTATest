#include "Particle.h"
#include "TCPTester.h"

// ALL_LEVEL, DEBUG_LEVEL
SerialDebugOutput debugOutput(9600, ALL_LEVEL);

SYSTEM_THREAD(ENABLED);

TCPTester tcpTester(IPAddress(65, 19, 178, 42), 7123);

const unsigned long CHECK_PERIOD_MS = 1000;
unsigned long lastCheck = 0;

void setup() {
	Serial.begin(9600);
	tcpTester.setup();
}

void loop() {
	tcpTester.loop();

	if (millis() - lastCheck >= CHECK_PERIOD_MS) {
		lastCheck = millis();

		Log.info("updatesPending=%d", System.updatesPending());
	}
}
