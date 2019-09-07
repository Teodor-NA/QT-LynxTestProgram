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
        transmitInterval(lynx, _lynxId)
        // blueLight(lynx.addVariable(lynxId, eUint8)),
        // orangeLight(lynx.addVariable(lynxId, eUint8)),
        // time(lynx.addVariable(lynxId, eUint32)),
        // transmitInterval(lynx.addVariable(lynxId, eUint32))
    {}

    LYNX_STRUCTURE_MACRO

	LynxVar_u8 blueLight;
	LynxVar_u8 orangeLight;
    LynxVar_u32 time;
    LynxVar_u32 transmitInterval;
};

#endif // !LIGHT_CONTROL_H
