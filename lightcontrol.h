#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include "lynxstructure.h"

using namespace LynxLib;

struct LightControl
{
	LightControl(LynxManager & lynx, char _structId) :
        lynxId(lynx.addStructure(_structId, 4)),
		blueLight(lynx.addVariable(lynxId, eUint8)),
        orangeLight(lynx.addVariable(lynxId, eUint8)),
        time(lynx.addVariable(lynxId, eUint32)),
        transmitInterval(lynx.addVariable(lynxId, eUint32))
    {}

	const LynxId lynxId;
	LynxVar_u8 blueLight;
	LynxVar_u8 orangeLight;
    LynxVar_u32 time;
    LynxVar_u32 transmitInterval;
};

#endif // !LIGHT_CONTROL_H
