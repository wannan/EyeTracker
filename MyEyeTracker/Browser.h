#ifndef __BROWSER_H__
#define __BROWSER_H__

#include <string>
#include <tobii/sdk/cpp/EyeTrackerBrowser.hpp>
#include <tobii/sdk/cpp/EyeTrackerBrowserFactory.hpp>

namespace tetio = tobii::sdk::cpp;

class Browser
{
public:
	Browser();
	void listEyeTrackers();
	void printEyeTrackerInfo(std::string& tracker_id);
	Tracker* getTracker(std::string& tracker_id);

private:	
	void onEyeTrackerBrowserEventList(tetio::EyeTrackerBrowser::event_type_t type, tetio::EyeTrackerInfo::pointer_t info);
	void onEyeTrackerBrowserEventPrintInfo(tetio::EyeTrackerBrowser::event_type_t type, tetio::EyeTrackerInfo::pointer_t info);
};

#endif
