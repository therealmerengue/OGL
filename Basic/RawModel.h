#pragma once
class RawModel
{
public:
	RawModel(int vaoID);
	~RawModel();

	int getVaoID() { return vaoID; }

private:
	int vaoID;
};

