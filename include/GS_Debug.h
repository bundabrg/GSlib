/**
 * GS_Debug, Created 2016 by Brendan Grieve (brendan at worldguard.com.au)
 *
 * This provides some debugging. We will write out to Serial just like using Serial.* functions but at the same
 * time once wireless is achieved we will start writing out to a multicast address (224.1.0.1 port 1223 hard coded for now)
 *
 * To listen for multicast on your dev machine the easiest way is to use socat in the following manner: -
 *   # socat UDP4-RECVFROM:1223,ip-add-membership=224.1.0.1:<your_own_real_ip>,fork -
 *
 *
 *  So if my machine that I want to listen for log events is IP 192.168.0.1, and my compiler machine (a vagrant sandbox with the toolchain to
 *  compile for the ESP) is 192.168.0.2, then I would use on 192.168.0.1: -
 *    # socat UDP4-RECVFROM:1223,ip-add-membership=224.1.0.1:192.168.0.1,fork -
 *
 *
 *  I could test this by starting (either in a new window or on another machine) the following:
 *    # socat STDIO UDP4-DATAGRAM:224.1.0.1:1223,range=192.168.0.0/24
 *
 *  which would then multicast anything I type into there to the other machine
 **/

#ifndef _BRG_GS_DEBUG_H
#define _BRG_GS_DEBUG_H

#include <Print.h>
#include <Network/UdpConnection.h>

class GS_Debug : public Print {
public:
	GS_Debug(void);
	~GS_Debug(void);

	/*template <typename T>
	void printf(String fmt, typename T);*/
	//void printf(const char* fmt, ...);


	//size_t write(const uint8_t *buffer, size_t size);
	size_t write(uint8_t);
	size_t write(const uint8_t *buffer, size_t size);

private:
	UdpConnection *_connection=0;

	void
		onClientData(UdpConnection& connection, char *data, int size, IPAddress remoteIP, uint16_t remotePort);

};

extern GS_Debug *gs_debug;

#endif // __BRG_GS_DEBUG_H

