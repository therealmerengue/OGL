#include "RawModel.h"

RawModel::RawModel(int vaoID) : size(1, 1, 2), position(0, 0, -5), rotationAxis(0, 1, -1), rotationAngle(20.0f)
{
	this->vaoID = vaoID;
}

RawModel::~RawModel()
{
}