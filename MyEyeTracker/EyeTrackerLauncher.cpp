#include "EyeTrackerLauncher.h"
#include "Browser.h"
#include "Calibrator.h"
#include "Tracker.h"
#include "MainLoopRunner.h"
#include <iostream>
#include <iomanip>
#include <boost/program_options.hpp>
#include <boost/thread.hpp>
#include <tobii/sdk/cpp/EyeTrackerBrowser.hpp>
#include <tobii/sdk/cpp/EyeTrackerBrowserFactory.hpp>
#include <tobii/sdk/cpp/EyeTrackerInfo.hpp>
#include <tobii/sdk/cpp/EyeTracker.hpp>

using ::std::string;
using ::std::cout;
using ::std::cerr;
using ::std::endl;
using ::std::ostream;

namespace options = boost::program_options;

using namespace tetio;

EyeTrackerLauncher::EyeTrackerLauncher() : trackerId(""), trackerFound(false){}

int EyeTrackerLauncher::run() {
	browseEyeTrackers();
	connectEyeTracker();
	runCalibration();
	return 1;
}

void EyeTrackerLauncher::browseEyeTrackers() {
	//Browser *browser = new Browser();
	//tracker = browser->getTracker(trackerId);
}

void EyeTrackerLauncher::connectEyeTracker() {
	if (tracker == NULL)
		return;
	runner.start();
	tracker->connectTo(runner.getMainLoop());
}
	
void EyeTrackerLauncher::runCalibration() {
	if (tracker == NULL)
		return;
	if (!tracker->isConnected()) {
		connectEyeTracker();
	}
	//Calibrator *calibrator = new Calibrator(tracker);
	//calibrator->...
}
	
void EyeTrackerLauncher::startTracking() {
	if (tracker == NULL) {
		return;
	}
	if (!tracker->isConnected()) {
		connectEyeTracker();
	}
	tracker->addGazeDataReceivedListener(boost::bind(&EyeTrackerLauncher::onGazeDataReceived, this, _1));
	tracker->startTracking();
}
	
void EyeTrackerLauncher::onGazeDataReceived(tetio::GazeDataItem::pointer_t data) {
	cout
		<< data->timestamp << " "
		<< data->leftGazePoint2d << " "
		<< data->rightGazePoint2d << " "
		<< endl;
}
	
void EyeTrackerLauncher::stopTracking() {
	if (tracker == NULL) {
		return;
	}
	if (tracker->isConnected()) {		
		tracker->stopTracking();
	}
}

void EyeTrackerLauncher::disconnectEyeTracker() {
	runner.stop();
}