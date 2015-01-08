#include "Tracker.h"
#include <tobii/sdk/cpp/EyeTrackerInfo.hpp>
#include <tobii/sdk/cpp/EyeTracker.hpp>

namespace tetio = tobii::sdk::cpp;

Tracker::Tracker(tetio::EyeTrackerInfo::pointer_t info): eyeTrackerInfo(info){}

void Tracker::connect(tetio::MainLoop& mainLoop) {
	eyeTracker = eyeTrackerInfo->getEyeTrackerFactory()->createEyeTracker(mainLoop);
	eyeTracker->addConnectionErrorListener(boost::bind(&Tracker::handleConnectionError, this, _1));
}

void Tracker::disconnect() {
	eyeTracker = NULL;
}

bool Tracker::isConnected() {
	return eyeTracker != NULL;
}

bool Tracker::addGazeDataReceivedListener(const tetio::EyeTracker::gaze_data_received_event_t::slot_type& listener){
	if (!this->isConnected())
		return false;

	eyeTracker->addGazeDataReceivedListener(listener);
	return true;
}
	
void Tracker::startTracking() {
	if (isConnected())
		eyeTracker->startTracking();
}
	
void Tracker::stopTracking() {
	if (isConnected())
		eyeTracker->stopTracking();
}

void Tracker::startCalibration() {
	if (isConnected())
		eyeTracker->startCalibration();
}

void Tracker::stopCalibration() {
	if (isConnected())
		eyeTracker->stopCalibration();
}

void Tracker::computeCalibrationAsync(const tetio::EyeTracker::async_callback_t &completedHandler) {
	if (isConnected())
		eyeTracker->computeCalibrationAsync(completedHandler);
}

bool Tracker::computeCalibration() {
	if (isConnected()) {
		try {
			eyeTracker->computeCalibration();
		}
		catch (tetio::EyeTrackerException e) {
			std::cout<<"errorCode: " + e.getErrorCode();
			return false;
		}		
		return true;
	}
	return false;
}

void Tracker::addCalibrationPointAsync(const tetio::Point2d &point2d, const tetio::EyeTracker::async_callback_t &completedHandler) {
	if (isConnected())
		eyeTracker->addCalibrationPointAsync(point2d, completedHandler);
}

void Tracker::addCalibrationPointAsync(const tetio::Point2d &point2d) {
	if (isConnected())
		eyeTracker->addCalibrationPoint(point2d);
}

void Tracker::removeCalibrationPoint(const tetio::Point2d& point) {
	if (isConnected())
		eyeTracker->removeCalibrationPoint(point);
}

tetio::Calibration::pointer_t Tracker::getCalibration() {
	if (isConnected())
		return eyeTracker->getCalibration();
	else 
		return NULL;
}


void Tracker::handleConnectionError(uint32_t errorCode) {
	eyeTracker.reset();
	//emit connectionError(errorCode);
}