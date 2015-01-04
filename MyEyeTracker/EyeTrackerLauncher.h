#ifndef __EYETRACKERLAUNCHER_H__
#define __EYETRACKERLAUNCHER_H__

#include "Tracker.h"
#include "MainLoopRunner.h"
#include <string>
#include <tobii/sdk/cpp/Library.hpp>

namespace tetio = tobii::sdk::cpp;

class EyeTrackerLauncher
{
public:
	EyeTrackerLauncher();
	int run();

private:
	void browseEyeTrackers();
	void connectEyeTracker();
	void runCalibration();
	void startTracking();
	void onGazeDataReceived(tetio::GazeDataItem::pointer_t data);
	void stopTracking();
	void disconnectEyeTracker();

	std::string trackerId;
	bool trackerFound;
	Tracker *tracker;
	MainLoopRunner runner;
};

#endif
