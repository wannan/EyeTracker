#include "TrackerController.h"
#include "Browser.h"

void TrackerController::startCalibration(int width, int height) {
	initGazeDataWrapper(width, height);
	browseEyeTrackers();
	connectEyeTracker();
	runCalibration();
}

void TrackerController::addCalibrationPoint(double x, double y) {
	calibrator->addCalibrationPoint(x, y);
}

void TrackerController::stopCalibration() {
	if (calibrator->stopCalibration()) {
		startTracking();
	}
	else {
		std::cout << "calibration failed";
	}
}

double TrackerController::getEyePositionX() {
	return gazeDataWrapper->getEyePositionX();
}

double TrackerController::getEyePositionY() {
	return gazeDataWrapper->getEyePositionY();
}

void TrackerController::initGazeDataWrapper(int width, int height) {
	gazeDataWrapper = new GazeDataWrapper();
	gazeDataWrapper->setAppWidth(width);
	gazeDataWrapper->setAppHeight(height);
}

void TrackerController::browseEyeTrackers() {
	Browser *browser = new Browser();
	tracker = browser->getTracker();
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
	calibrator = new Calibrator(tracker);
	calibrator->startCalibration();
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