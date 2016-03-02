/**
 * GS Update - Created 2016, Brendan Grieve (brendan@worldguard.com.au)
 */

#include <GS_Update.h>
#include <SmingCore/Network/HttpClient.h>
#include <HardwareSerial.h>
#include <SmingCore/Network/rBootHttpUpdate.h>

#include "GS_Debug.h"

extern char const GS_BUILD_NUMBER[];

ICACHE_FLASH_ATTR
GS_Update::GS_Update(void) {

}

ICACHE_FLASH_ATTR
GS_Update::GS_Update(UpdateCompleteDelegate UpdateCompleteCB) :
	_update_complete_cb(UpdateCompleteCB)
{
}

ICACHE_FLASH_ATTR
GS_Update::~GS_Update(void) {
	delete _client;
}


/**
 * Check if an update exists on our update server.
 *
 * We download the version, and compare it to our version
 */
ICACHE_FLASH_ATTR
void
GS_Update::checkForUpdate(void) {
	gs_debug->print("[Update]: Checking for new updates\n");


	_client = new HttpClient();
	_client->downloadString("http://172.x.x.x/gs_version", HttpClientCompletedDelegate(&GS_Update::_checkForUpdateComplete, this));
}

ICACHE_FLASH_ATTR
void
GS_Update::_checkForUpdateComplete(HttpClient& client, bool successful) {
	String version = _client->getResponseString();
	version.trim();

	if (String(GS_BUILD_NUMBER) == version ) {
		// Call call back it needed
		if (_update_complete_cb) {
			_update_complete_cb(true);
		}
		gs_debug->print("[Update]: No new updates found\n");

		return;
	}

	gs_debug->printf("[Update]: New update found (Old: %s, New:%s)\n", GS_BUILD_NUMBER, version.c_str());

	// We have a mismatch so lets download new rom
	otaUpdater = new rBootHttpUpdate();
	int slot = rboot_get_current_rom();
	rboot_config bootconf = rboot_get_config();

	if (slot==1) {
		otaUpdater->addItem(bootconf.roms[0], "http://172.x.x.x/rom0.bin");
		otaUpdater->switchToRom(0);
	} else {
		otaUpdater->addItem(bootconf.roms[1], "http://172.x.x.x/rom1.bin");
		otaUpdater->switchToRom(1);
	}
	otaUpdater->start();
}

