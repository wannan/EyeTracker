#ifndef __TRACKER_H__
#define __TRACKER_H__

#include <string>
#include <tobii/sdk/cpp/EyeTrackerInfo.hpp>
#include <tobii/sdk/cpp/EyeTrackerFactory.hpp>
#include <tobii/sdk/cpp/EyeTracker.hpp>

namespace tetio = tobii::sdk::cpp;

class Tracker
{
public:
	Tracker(tetio::EyeTrackerInfo::pointer_t info);
	void connectTo(tetio::MainLoop& mainLoop);
	bool isConnected();
	bool addGazeDataReceivedListener(const tetio::EyeTracker::gaze_data_received_event_t::slot_type& listener);
	void startTracking();
	void stopTracking();
	void startCalibration();
	void stopCalibration();
	void computeCalibrationAsync(const tetio::EyeTracker::async_callback_t &completedHandler);
	void addCalibrationPointAsync(const tetio::Point2d &point2d,
		const tetio::EyeTracker::async_callback_t &completedHandler);
	tetio::Calibration::pointer_t getCalibration();

private:
	void handleConnectionError(uint32_t errorCode);
	tobii::sdk::cpp::EyeTrackerInfo::pointer_t eyeTrackerInfo;
	tetio::EyeTracker::pointer_t eyeTracker;
};

#endif
