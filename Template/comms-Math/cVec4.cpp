#include "comms-Math.h"

namespace comms {

const cVec4 cVec4::Zero(0.0f);
const cVec4 cVec4::One(1.0f);
const cVec4 cVec4::Infinity(cMath::FloatMaxValue);
const cVec4 cVec4::AxisX(1.0f, 0.0f, 0.0f, 0.0f);
const cVec4 cVec4::AxisY(0.0f, 1.0f, 0.0f, 0.0f);
const cVec4 cVec4::AxisZ(0.0f, 0.0f, 1.0f, 0.0f);
const cVec4 cVec4::AxisW(0.0f, 0.0f, 0.0f, 1.0f);
const cVec4 cVec4::AxisNegX(-1.0f, 0.0f, 0.0f, 0.0f);
const cVec4 cVec4::AxisNegY(0.0f, -1.0f, 0.0f, 0.0f);
const cVec4 cVec4::AxisNegZ(0.0f, 0.0f, -1.0f, 0.0f);
const cVec4 cVec4::AxisNegW(0.0f, 0.0f, 0.0f, -1.0f);

// cVec4::ToString
const cStr cVec4::ToString(const int Prec) const {
	return cStr::ToString(ToFloatPtr(), GetDimension(), Prec);
}

// cVec4::operator =
const cVec4 & cVec4::operator = (const cVec3 &orig) {
	x = orig.x;
	y = orig.y;
	z = orig.z;
	w = 1.0f;
	return *this;
}

} // comms
