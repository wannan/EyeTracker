#include "Calibrator.h"
#include <boost/make_shared.hpp>

using namespace std;
using namespace tetio;

#define CALIBRATION_POINT_INTERVAL	1000 //ms

Calibrator::Calibrator(Tracker *tracker) :
tracker(tracker)
{
}

Calibration::pointer_t Calibrator::runCalibration()
{
	createPointList();

	// Inform the eyetracker that we want to run a calibration
	tracker->startCalibration();

	QPalette pal = m_calibrationDlg.palette();
	pal.setColor(m_calibrationDlg.backgroundRole(), Qt::gray);
	m_calibrationDlg.setPalette(pal);
	m_calibrationDlg.setWindowState(m_calibrationDlg.windowState() | Qt::WindowFullScreen);
	m_calibrationDlg.clearCalibrationPoint();
	m_calibrationDlg.exec();

	// Inform the eyetracker that we have finished
	// the calibration routine
	tracker->stopCalibration();

	return m_calibrationResult;
}


void Calibrator::startNextOrFinish()
{
	if (m_calibrationPoints.size() > 0) {
		Point2d point = m_calibrationPoints.front();
		m_calibrationPoints.pop();
		m_calibrationDlg.drawCalibrationPoint(point);
		m_sleepTimer.start(CALIBRATION_POINT_INTERVAL);
	}
	else {
		// Use the async version of ComputeCalibration since
		// this call takes some time
		tracker->computeCalibrationAsync(boost::bind(&Calibrator::computeCompleted, this, _1));
	}
}


void Calibrator::timerTickHandler()
{
	m_sleepTimer.stop();
	Point2d point = m_calibrationDlg.getCalibrationPoint();
	tracker->addCalibrationPointAsync(point, boost::bind(&Calibrator::pointCompleted, this, _1));
}

void Calibrator::pointCompleted(uint32_t)
{
	emit pointCompletedEvent();
}

void Calibrator::pointCompletedHandler()
{
	m_calibrationDlg.clearCalibrationPoint();
	startNextOrFinish();
}

void Calibrator::computeCompleted(uint32_t e)
{
	if (e == 0)
		emit computeCompletedEvent();
	else
		emit computeFailedEvent();
}

void Calibrator::computeCompletedHandler()
{
	m_calibrationDlg.close();
	Calibration::pointer_t temp = tracker->getCalibration();
	m_calibrationResult = boost::make_shared<CalibrationImpl>(temp->getRawData());
}

void Calibrator::computeFailedHandler()
{
	m_calibrationDlg.close();
	m_calibrationResult = boost::shared_ptr<CalibrationImpl>();
}

void Calibrator::createPointList()
{
	m_calibrationPoints.push(Point2d(0.1, 0.1));
	m_calibrationPoints.push(Point2d(0.5, 0.5));
	m_calibrationPoints.push(Point2d(0.9, 0.1));
	m_calibrationPoints.push(Point2d(0.9, 0.9));
	m_calibrationPoints.push(Point2d(0.1, 0.9));
}

void Calibrator::abortCalibrationHandler()
{
	m_sleepTimer.stop();
	m_calibrationDlg.close();
}


