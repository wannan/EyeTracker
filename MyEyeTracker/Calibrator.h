#ifndef __CALIBRATOR_H__
#define __CALIBRATOR_H__

#include "Tracker.h"
#include <queue>
#include <boost/shared_ptr.hpp>
#include <tobii/sdk/cpp/EyeTracker.hpp>

namespace tetio = tobii::sdk::cpp;

class Calibrator
{
public:
	Calibrator(Tracker *t);
	tetio::Calibration::pointer_t runCalibration();
	void pointCompletedEvent();
	void computeCompletedEvent();
	void computeFailedEvent();
	void abortCalibrationEvent();

private:
	void startNextOrFinish();
	void timerTickHandler();
	void pointCompletedHandler();
	void abortCalibrationHandler();
	void computeCompletedHandler();
	void computeFailedHandler();
	void createPointList();
	void pointCompleted(uint32_t e);
	void computeCompleted(uint32_t e);

	Tracker *tracker;
	std::queue<tetio::Point2d> m_calibrationPoints;
	tetio::Calibration::pointer_t m_calibrationResult;

};

#endif