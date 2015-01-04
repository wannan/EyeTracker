#ifndef __GAZEDATAWRAPPER_H__
#define __GAZEDATAWRAPPER_H__

#include <tobii/sdk/cpp/GazeDataItem.hpp>

namespace tetio = tobii::sdk::cpp;

class GazeDataWrapper
{
public:
	GazeDataWrapper();
	double getEyePositionX();
	double getEyePositionY();
	void setAppWidth(int w);
	void setAppHeight(int h);
	void setGazeRawData(tetio::GazeDataItem::pointer_t data);

private:
	void calEyePosition(double leftX, double leftY, double rightX, double rightY);
	void setEyePositionX(double x);
	void setEyePositionY(double y);
	double eyePositionX;
	double eyePositionY;
	int appWidth;
	int appHeight;
};

#endif
