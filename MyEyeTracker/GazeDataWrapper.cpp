#include "GazeDataWrapper.h"
#include <tobii/sdk/cpp/GazeDataItem.hpp>

namespace tetio = tobii::sdk::cpp;

GazeDataWrapper::GazeDataWrapper():eyePositionX(0), eyePositionY(0),appWidth(0),appHeight(0) {};

double GazeDataWrapper::getEyePositionX() {
	return eyePositionX;
}

double GazeDataWrapper::getEyePositionY() {
	return eyePositionY;
}

void GazeDataWrapper::setAppWidth(int w) {
	appWidth = w;
}

void GazeDataWrapper::setAppHeight(int h) {
	appHeight = h;
}

void GazeDataWrapper::setGazeRawData(tetio::GazeDataItem::pointer_t data) {
	tetio::Point2d leftEye = data->leftGazePoint2d;
	tetio::Point2d rightEye = data->rightGazePoint2d;
	calEyePosition(leftEye.x, leftEye.y, rightEye.x, rightEye.y);
}

void GazeDataWrapper::calEyePosition(double leftX, double leftY, double rightX, double rightY) {
	double middleX = (leftX + rightX) / 2;
	double middleY = (leftY + rightY) / 2;
	setEyePositionX(middleX * appWidth);
	setEyePositionY(middleY * appHeight);
}
	
void GazeDataWrapper::setEyePositionX(double x) {
	eyePositionX = x;
}
	
void GazeDataWrapper::setEyePositionY(double y) {
	eyePositionY = y;
}