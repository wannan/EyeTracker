#include "Tracker.h"
#include <tobii/sdk/cpp/EyeTrackerInfo.hpp>
#include <tobii/sdk/cpp/EyeTracker.hpp>

namespace tetio = tobii::sdk::cpp;

Tracker::Tracker(tetio::EyeTrackerInfo::pointer_t info): eyeTrackerInfo(info){}

void Tracker::connectTo(tetio::MainLoop& mainLoop) {
	eyeTracker = eyeTrackerInfo->getEyeTrackerFactory()->createEyeTracker(mainLoop);
	eyeTracker->addConnectionErrorListener(boost::bind(&Tracker::handleConnectionError, this, _1));
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

void Tracker::handleConnectionError(uint32_t errorCode)
{
	eyeTracker.reset();
	//emit connectionError(errorCode);
}