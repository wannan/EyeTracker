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
	void connect(tetio::MainLoop& mainLoop);
	void disconnect();
	bool isConnected();
	bool addGazeDataReceivedListener(const tetio::EyeTracker::gaze_data_received_event_t::slot_type& listener);
	void startTracking();
	void stopTracking();
	void startCalibration();
	void stopCalibration();
	/*
	异步计算校准数据，参数completedHandler为计算完毕后的回调函数
	*/
	void computeCalibrationAsync(const tetio::EyeTracker::async_callback_t &completedHandler);
	bool computeCalibration();
	/*
	异步添加校准点，参数completedHandler为添加完毕后的回调函数，此方法给回调函数传入一个uint32_t类型的参数e，当e为0则校准成功，否则失败
	*/
	void addCalibrationPointAsync(const tetio::Point2d &point, const tetio::EyeTracker::async_callback_t &completedHandler);
	void addCalibrationPoint(const tetio::Point2d &point);

private:
	void handleConnectionError(uint32_t errorCode);
	tobii::sdk::cpp::EyeTrackerInfo::pointer_t eyeTrackerInfo;
	tetio::EyeTracker::pointer_t eyeTracker;
};

#endif
