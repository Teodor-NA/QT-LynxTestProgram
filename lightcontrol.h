#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include "lynxstructure.h"

using namespace LynxLib;

struct LightControl
{
	LightControl(LynxManager & lynx, char _structId) :
        _lynxId(lynx.addStructure(_structId, 4)),
        blueLight(lynx, _lynxId),
        orangeLight(lynx, _lynxId),
        time(lynx, _lynxId),
        transmitInterval(lynx, _lynxId),
        state(lynx, _lynxId)
    {}

    LYNX_STRUCTURE_MACRO

	LynxVar_u8 blueLight;
	LynxVar_u8 orangeLight;
    LynxVar_u32 time;
    LynxVar_u32 transmitInterval;
    LynxVar_string state;
};

#endif // !LIGHT_CONTROL_H
