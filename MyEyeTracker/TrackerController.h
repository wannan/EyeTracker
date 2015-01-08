#include "Browser.h"
#include "Calibrator.h"
#include ""

Class TrackerController{ 
public:
	void startCalibration(int width, int height);
	void addPoint(double, double);
	void stopCalibration();
	double getEyePositionX();
	double getEyePositionY();

}

