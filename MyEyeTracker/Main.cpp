#include "TrackerController.h"
#include <tobii/sdk/cpp/Library.hpp>
#include <windows.h>

namespace tetio = tobii::sdk::cpp;

#define CALIBRATION_POINT_INTERVAL	1000 //ms

int main(int argc, char *argv[])
{
	tetio::Library::init();
	std::cout << "test running..." << std::endl;
	TrackerController *controller = new TrackerController();
	controller->startCalibration(200, 400);
	controller->addCalibrationPoint(0.5, 0.5);
	std::cout << "sleep..." << std::endl;
	Sleep(CALIBRATION_POINT_INTERVAL);
	std::cout << "wakeup..." << std::endl;
	controller->stopCalibration();
	boost::this_thread::sleep(boost::posix_time::seconds(3));
	controller->disconnect();
	std::cout << controller->getEyePositionX() << " " << controller->getEyePositionY();
	int a;
	std::cin >> a;
	return 1;
}