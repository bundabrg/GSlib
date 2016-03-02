#include <user_config.h>
#include <SmingCore/SmingCore.h>

#include <GS_Debug.h>
#include <GS_Update.h>

#define WIFI_NETWORK "change_me"
#define WIFI_KEY "change_me"

GS_Debug *gs_debug;
GS_Update *gs_update;

// Pulled in from timestamp.c which is generated at build time (see Makefile-user.mk)
extern char const GS_BUILD_NUMBER[];

void
ICACHE_FLASH_ATTR
updateComplete(bool successful) {
	gs_debug->printf("[UpdateComplete]: This line is reached if no new updates were found\n");

	// successful not used yet
}


void
ICACHE_FLASH_ATTR
connectOk() {
	gs_debug->printf("[INIT]: Network Active (%s)\n", GS_BUILD_NUMBER);

	// Initialise our Updater and check for updates
	gs_update = new GS_Update( updateComplete );
	gs_update->checkForUpdate();
}


void
ICACHE_FLASH_ATTR
init() {
	// Debugging Stuff
	system_set_os_print(0);
	Serial.systemDebugOutput(false);

	gs_debug = new GS_Debug();
	gs_debug->printf("[INIT]: Starting (%s)\n", GS_BUILD_NUMBER);

	int slot = rboot_get_current_rom();
	gs_debug->printf("[INIT}: Currently running rom %d.\n", slot);

	// Connect to a Wifi network. Call connectOk() on connection
	WifiStation.config(WIFI_NETWORK,WIFI_KEY);
	WifiAccessPoint.enable(false);
	WifiStation.enable(true);
	WifiStation.waitConnection(connectOk);

	gs_debug->print("[INIT]: Finished Setting Up\n");
}
