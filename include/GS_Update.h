/**
 * GS_Update, Created 2016 by Brendan Grieve (brendan at worldguard.com.au)
 *
 * A very simplistic OTA updater. We download from our web site a file 'gs_version', and compare its contents to
 * a variable GS_BUILD_NUMBER, which is generated at build time. If it is different then we download the appropriate
 * rom and boot into it.
 *
 * This assume we are using a 2 rom system.
 *
 **/

#ifndef _BRG_GS_UPDATE_H
#define _BRG_GS_UPDATE_H

#include <Delegate.h>

class HttpClient;
class rBootHttpUpdate;


typedef Delegate<void(bool successful)> UpdateCompleteDelegate;

class GS_Update {
public:
	GS_Update(void);
	GS_Update(UpdateCompleteDelegate UpdateCompleteCB);
	~GS_Update(void);

	void checkForUpdate(void);


private:
	rBootHttpUpdate* otaUpdater = 0;
	HttpClient *_client = 0;

	UpdateCompleteDelegate _update_complete_cb;

	void
		_checkForUpdateComplete(HttpClient& client, bool successful);

};

#endif // __BRG_GS_UPDATE_H
