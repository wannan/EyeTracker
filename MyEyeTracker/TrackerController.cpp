#include "TrackerController.h"
#include "Browser.h"

void TrackerController::startCalibration(int width, int height) {
	initGazeDataWrapper(width, height);
	browseEyeTrackers();
	connectEyeTracker();
	runCalibration();
}

void TrackerController::addCalibrationPoint(double x, double y) {
	if (calibrator == NULL)
		return;
	std::cout << "TrackerController::addCalibrationPoint(" << x << "," << y << ")" << std::endl;
	calibrator->addCalibrationPoint(x, y);
}

void TrackerController::stopCalibration() {
	if (calibrator == NULL)
		return;
	std::cout << "TrackerController::stopCalibration()" << std::endl;
	if (calibrator->stopCalibration()) {
		startTracking();
	}
	else {
		std::cout << "calibration failed" << std::endl;
		startTracking();
	}
}

double TrackerController::getEyePositionX() {
	return gazeDataWrapper->getEyePositionX();
}

double TrackerController::getEyePositionY() {
	return gazeDataWrapper->getEyePositionY();
}

void TrackerController::initGazeDataWrapper(int width, int height) {
	std::cout << "TrackerController::initGazeDataWrapper(" << width << ", " << height << ")" << std::endl;
	gazeDataWrapper = new GazeDataWrapper();
	gazeDataWrapper->setAppWidth(width);
	gazeDataWrapper->setAppHeight(height);
}

void TrackerController::browseEyeTrackers() {
	Browser *browser = new Browser();
	trackerId = "TX060-301-20900183";   // give the specified tracker ID for test
	tracker = browser->getTracker(trackerId);
}

void TrackerController::connectEyeTracker() {
	if (tracker == NULL) {
		std::cout << "tracker is NULL" << std::endl;
		return;
	}		
	std::cout << "TrackerController::connectEyeTracker()" << std::endl;
	runner.start();
	tracker->connect(runner.getMainLoop());
}

void TrackerController::runCalibration() {
	if (tracker == NULL)
		return;
	if (!tracker->isConnected()) {
		connectEyeTracker();
	}
	std::cout << "TrackerController::runCalibration()" << std::endl;
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
	std::cout << "TrackerController::startTracking()" << std::endl;
	tracker->addGazeDataReceivedListener(boost::bind(&TrackerController::onGazeDataReceived, this, _1));
	tracker->startTracking();
}

void TrackerController::onGazeDataReceived(tetio::GazeDataItem::pointer_t data) {
	std::cout << "TrackerController::onGazeDataReceived()" << std::endl;
	gazeDataWrapper->setGazeRawData(data);
}

void TrackerController::disconnect() {
	tracker->stopTracking();
	tracker->disconnect();
}