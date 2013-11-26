#pragma once

#include "PersonVo.h"

class PartenerVo : public PersonVo
{
public:

	PartenerVo(void);
	virtual ~PartenerVo(void);

	bool init();
	CREATE_FUNC(PartenerVo);
};