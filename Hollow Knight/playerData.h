#pragma once
#include "singletonBase.h"

class playerData : public singletonBase <playerData>
{
private:

public:
	HRESULT init();
	void release();

	playerData() {}
	~playerData() {}
};

