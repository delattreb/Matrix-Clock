//
// Created by Bruno on 30/06/2017.
//

#include "RTClib.h"
#include "var.h"


class rtcAccess {

private:

	DS1307 rtc;

public:

	bool timeset = false;

	rtcAccess() {
	}

	~rtcAccess() {
	}

	void init() {
#ifdef DEBUG
		Serial.println("Test RTC");
#endif 
		rtc.begin();
		if (!rtc.isrunning()) {
#ifdef DEBUG
			Serial.println("RTC is NOT running");
#endif 
			rtc.adjust(DateTime(__DATE__, __TIME__));
#ifdef DEBUG
			Serial.println("Date and time adjusted");
#endif 
		}
		else {
#ifdef DEBUG
			Serial.println("RTC is running");
#endif 
		}
	}

	DateTime getDateTime() {
		DateTime now = rtc.now();
		return now;
	}

	String getDateStr()
	{
		DateTime now = rtc.now();
		return String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
	}

	String getTimeStr() {
		DateTime now = rtc.now();
		return String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
	}

	String getTimeStrRaw() {
		DateTime now = rtc.now();
		return String(now.hour()) + String(now.minute())  + String(now.second());
	}
};



