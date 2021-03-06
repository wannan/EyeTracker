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
	void startCalibration();
	bool stopCalibration();
	void addCalibrationPoint(double x, double y);
	/*void pointCompletedEvent();
	void computeCompletedEvent();
	void computeFailedEvent();
	void abortCalibrationEvent();*/

private:
	/*tetio::Calibration::pointer_t runCalibration();
	void startNextOrFinish();
	void timerTickHandler();
	void pointCompletedHandler();
	void abortCalibrationHandler();
	void computeCompletedHandler();
	void computeFailedHandler();
	void createPointList();
	void pointCompleted(uint32_t e);
	void computeCompleted(uint32_t e);*/

	Tracker *tracker;
	//std::queue<tetio::Point2d> m_calibrationPoints;
	//tetio::Calibration::pointer_t m_calibrationResult;

};

#endif