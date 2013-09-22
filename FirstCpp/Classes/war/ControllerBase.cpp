#include "ControllerBase.h"


ControllerBase::ControllerBase(void)
{
}


ControllerBase::~ControllerBase(void)
{
}

void ControllerBase::setControllerListener(ControllerListener* controllerListener)
{
	mControllerLintoner = controllerListener;
}

void ControllerBase::moveTo(CCPoint targetPos)
{

}

//void ControllerBase::checkTargetPos()
//{
//
//}