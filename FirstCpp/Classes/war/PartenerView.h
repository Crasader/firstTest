#pragma once
#include "personview.h"

class PartenerView :
	public PersonView
{
public:
	PartenerView(void);
	virtual ~PartenerView(void);

	CREATE_FUNC(PartenerView);
	virtual bool init();
};

