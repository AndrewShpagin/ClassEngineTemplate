#include "comms-Math.h"

namespace comms {

const dVec4 dVec4::Zero(0.0);
const dVec4 dVec4::One(1.0);
const dVec4 dVec4::Infinity(cMath::FloatMaxValue);
const dVec4 dVec4::AxisX(1.0, 0.0, 0.0, 0.0);
const dVec4 dVec4::AxisY(0.0, 1.0, 0.0, 0.0);
const dVec4 dVec4::AxisZ(0.0, 0.0, 1.0, 0.0);
const dVec4 dVec4::AxisW(0.0, 0.0, 0.0, 1.0);
const dVec4 dVec4::AxisNegX(-1.0, 0.0, 0.0, 0.0);
const dVec4 dVec4::AxisNegY(0.0, -1.0, 0.0, 0.0);
const dVec4 dVec4::AxisNegZ(0.0, 0.0, -1.0, 0.0);
const dVec4 dVec4::AxisNegW(0.0, 0.0, 0.0, -1.0);

// dVec4::ToString
const cStr dVec4::ToString(const int Prec) const {
	return cStr::ToString(ToFloatPtr(), GetDimension(), Prec);
}

// dVec4::operator =
const dVec4 & dVec4::operator = (const dVec3 &orig) {
	x = orig.x;
	y = orig.y;
	z = orig.z;
	w = 1.0;
	return *this;
}

} // comms
