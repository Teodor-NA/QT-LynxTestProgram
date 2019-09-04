#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include "lynxstructure.h"

using namespace LynxLib;

struct LightControl
{
	LightControl(LynxManager & lynx, char _structId) :
		lynxId(lynx.addStructure(_structId, 2)),
		blueLight(lynx.addVariable(lynxId, eUint8)),
		orangeLight(lynx.addVariable(lynxId, eUint8))
	{}

	const LynxId lynxId;
	LynxVar_u8 blueLight;
	LynxVar_u8 orangeLight;
};

#endif // !LIGHT_CONTROL_H