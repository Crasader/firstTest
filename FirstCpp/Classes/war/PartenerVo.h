#pragma once

#include "PersonVo.h"

class PartenerVo : public PersonVo
{
public:

	PartenerVo(void);
	~PartenerVo(void);

	bool init();
	CREATE_FUNC(PartenerVo);
};