#pragma once
#include "personview.h"

class PartenerView :
	public PersonView
{
public:
	PartenerView(void);
	~PartenerView(void);

	CREATE_FUNC(PartenerView);
	virtual bool init();
};

