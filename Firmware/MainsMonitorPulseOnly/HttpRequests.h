// HttpRequests.h

#ifndef _HTTPREQUESTS_h
#define _HTTPREQUESTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class HttpRequestsClass
{
 protected:


 public:
	void init();
};

extern HttpRequestsClass HttpRequests;

#endif
