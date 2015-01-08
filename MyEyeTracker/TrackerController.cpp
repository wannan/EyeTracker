#include "TrackerController.h"

void TrackerController::startCalibration(int width, int height) {
	gazeDataWrapper = new GazeDataWrapper();
	gazeDataWrapper->setAppWidth(width);
	gazeDataWrapper->setAppHeight(height);

	browseEyeTrackers();
	connectEyeTracker();
	runCalibration();
}

void TrackerController::addCalibrationPoint(double x, double y) {
	
}

void TrackerController::stopCalibration() {
	tracker->stopCalibration();
	startTracking();
}

double TrackerController::getEyePositionX() {
	return gazeDataWrapper->getEyePositionX();
}

double TrackerController::getEyePositionY() {
	return gazeDataWrapper->getEyePositionY();
}

void TrackerController::browseEyeTrackers() {
	//Browser *browser = new Browser();
	//tracker = browser->getTracker(trackerId);
}

void TrackerController::connectEyeTracker() {
	if (tracker == NULL)
		return;
	runner.start();
	tracker->connect(runner.getMainLoop());
}

void TrackerController::runCalibration() {
	if (tracker == NULL)
		return;
	if (!tracker->isConnected()) {
		connectEyeTracker();
	}
	//Calibrator *calibrator = new Calibrator(tracker);
	//calibrator->...
}

void TrackerController::startTracking() {
	if (tracker == NULL) {
		return;
	}
	if (!tracker->isConnected()) {
		connectEyeTracker();
	}

	tracker->addGazeDataReceivedListener(boost::bind(&TrackerController::onGazeDataReceived, this, _1));
	tracker->startTracking();
}

void TrackerController::onGazeDataReceived(tetio::GazeDataItem::pointer_t data) {
	gazeDataWrapper->setGazeRawData(data);
}