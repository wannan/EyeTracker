//#include "EyeTrackerLauncher.h"
#include "TrackerController.h"
#include <tobii/sdk/cpp/Library.hpp>
#include <windows.h>

namespace tetio = tobii::sdk::cpp;

#define CALIBRATION_POINT_INTERVAL	1000 //ms

int main(int argc, char *argv[])
{
	tetio::Library::init();
	//return EyeTrackerLauncher().run();
	std::cout << "test running..." << std::endl;
	TrackerController *controller = new TrackerController();
	controller->startCalibration(200, 400);
	controller->addCalibrationPoint(0.5, 0.5);
	std::cout << "sleep..." << std::endl;
	Sleep(CALIBRATION_POINT_INTERVAL);
	std::cout << "wakeup..." << std::endl;
	controller->stopCalibration();
	std::cout << controller->getEyePositionX() << " " << controller->getEyePositionY();
	return 1;
}