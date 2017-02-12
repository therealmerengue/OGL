#include "RawModel.h"

RawModel::RawModel(int vaoID, Coordinates coordinates) : coordinates(coordinates)
{
	this->vaoID = vaoID;
}

RawModel::~RawModel()
{
}