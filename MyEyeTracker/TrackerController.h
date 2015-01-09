#ifndef __TRACKERCONTROLLER_H__
#define __TRACKERCONTROLLERR_H__

#include "Tracker.h"
#include "MainLoopRunner.h"
#include "GazeDataWrapper.h"
#include "Calibrator.h"
#include <string>
#include <tobii/sdk/cpp/Library.hpp>

class TrackerController{ 
public:
	void startCalibration(int width, int height);
	void addCalibrationPoint(double x, double y);
	void stopCalibration();
	double getEyePositionX();
	double getEyePositionY();

private:
	void initGazeDataWrapper(int width, int height);
	void browseEyeTrackers();
	void connectEyeTracker();
	void runCalibration();
	void startTracking();
	void onGazeDataReceived(tetio::GazeDataItem::pointer_t data);

	std::string trackerId;
	MainLoopRunner runner;
	GazeDataWrapper *gazeDataWrapper;
	Tracker *tracker;
	Calibrator *calibrator;
};

#endif