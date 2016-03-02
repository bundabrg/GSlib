/**
 * GS Debug Code - Created 2016, Brendan Grieve (brendan@worldguard.com.au)
 */

#include <GS_Debug.h>
#include <HardwareSerial.h>
#include <Network/UdpConnection.h>

ICACHE_FLASH_ATTR
GS_Debug::GS_Debug(void) {
	Serial.begin(115200);
	//Serial.systemDebugOutput(true);

	// Setup Debug server
	typedef Delegate<void(UdpConnection& connection, char *data, int size, IPAddress remoteIP, uint16_t remotePort)> UdpConnectionDataDelegate;

	_connection = new UdpConnection( UdpConnectionDataDelegate(&GS_Debug::onClientData, this));

	// @Todo: IP and port should not be hard coded in
	_connection->connect(IPAddress("224.1.0.1"), 1223);
}


ICACHE_FLASH_ATTR
GS_Debug::~GS_Debug(void) {

}

ICACHE_FLASH_ATTR
size_t
GS_Debug::write(uint8_t buf) {
	size_t n = Serial.write(buf);

	if (_connection) {
		char b[2];

		b[0] = buf;b[1] = 0;
		_connection->send(b,1);
	}

	return n;
}

/**
 * Write a full string
 */
ICACHE_FLASH_ATTR
size_t
GS_Debug::write(const uint8_t *buffer, size_t size) {
	// Write out line to UDP
	if (_connection) {
		_connection->send((const char*) buffer, size);
	}

	// Write serial one byte at a time
	size_t n = 0;
	const uint8_t *b = buffer;
	while (size--) {
		n += Serial.write(*b++);
	}



	return n;
}



/**
 * onClientData
 *
 * UDP Client has sent us some data which we promptly ignore
 */
ICACHE_FLASH_ATTR
void
GS_Debug::onClientData(UdpConnection& connection, char *data, int size, IPAddress remoteIP, uint16_t remotePort) {

}

